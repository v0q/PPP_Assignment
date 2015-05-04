/*
 Copyright © 2015 Teemu Lindborg
 SDAGE 1st year 2nd PPP Assignment
*/

#ifdef LINUX
  #include <GL/gl.h>
#endif
#ifdef DARWIN
  #include <OpenGL/gl.h>
#endif

#include <iostream>
#include <ctime>

#include "Defs.h"
#include "Camera.h"
#include "Player.h"
#include "Projectile.h"
#include "TextureOBJ.h"
#include "World.h"
#include "NCCA/GLFunctions.h"

// ---------------------------------------------------------------------------------------
/// @file Player.cpp
/// @brief Implementation of the player class functions
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------
Player::Player(
               const float _x,
               const float _y,
               const float _z
              ) :
               m_score(0),
               m_pos(_x, _y, _z, 1.0f),
               m_aimDir(0.0f),
               m_rot(0.0f),
               m_turn(0.0f),
               m_xMov(0.0f),
               m_yMov(0.0f),
               m_life(100)
{
  // Loading in the ship model and textures
  loadModel("models/ss.obj", m_ship);

  loadTexture("textures/projectile4.png", m_particleTexId);
  loadTexture("textures/animated_explosion.png", m_projectileId);

  // This is a bit of a hacky solution as the models (vertices, texture coordinates etc)
  // were rotated 90 degrees ccw on the uni machines so we're using a rotated texture
  // and rotating the actual model 90 degrees cw. If the ships' flying sideways and
  // textures are not showing up properly, remove the #ifdef LINUX parts and leave in
  // the DARWIN ones where ever I've flagged it as //HACKY SOLUTION

// HACKY SOLUTION START
#ifdef LINUX
  loadTexture("textures/ss_texture_90.png", m_shipTexId);
#endif
#ifdef DARWIN
  loadTexture("textures/ss_texture.png", m_shipTexId);
#endif
// HACKY SOLUTION END

  // Generates the displaylist from the model data
  ship();

  // Loads the firing sound and background noise and start the background noise
  audio::loadSound("sounds/flame.wav", &s_aFire);
  audio::loadSound("sounds/bg_sound.ogg", &s_bgSound);
  Mix_PlayMusic(s_bgSound, -1);
  Mix_VolumeMusic(MIX_MAX_VOLUME * 0.1f);
}
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------
Player::~Player()
{
  // Clear the projectile and particle vectors and free
  // up the memory used by the player class
  m_p.clear();
  std::vector<Projectile>().swap(m_p);
  m_particles.clear();
  std::vector<Particle>().swap(m_particles);

  freeModelMem(m_ship);

  Mix_FreeChunk(s_aFire);
  Mix_FreeMusic(s_bgSound);
}
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------
bool Player::isAlive()
{
  return (m_life > 0 ? true : false);
}
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------
void Player::drawPlayer()
{
    // Moving and orienting the player to the camera
    glMultMatrixf(m_orientation.m_openGL);
    glLoadIdentity();

    glPointSize(15.0f);

    // Move player to the correct position
    glTranslatef(m_xMov, m_yMov, -m_pos.length() + WORLDRADIUS + PLAYEROFFSET);

    // For the time being the cannon is just a gl point
    glBegin(GL_POINTS);
      glColor3f(0, 0, 0);
      glVertex3f(0.1*cosf(m_aimDir), 0.1*sinf(m_aimDir), 0);
    glEnd();

// HACKY SOLUTION START
#ifdef LINUX
    glRotatef(-90, 0, 0, 1);
#endif
// HACKY SOLUTION END

    // Rotate and tilt the player based on the movement
    glRotatef(m_rot, 0, 0, 1);
    glRotatef(m_turn, 0, 1, 0);

    glColor3f(1.0f, 0.0, 0.0f);
    glCallLists(m_displayList.size(), GL_UNSIGNED_INT, &m_displayList[0]);
}
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------
void Player::handleMovement(
                            SDL_GameController *_c,
                            Camera &io_cam
                           )
{
  const Uint8 *keystate = SDL_GetKeyboardState(NULL);

  // Variables for controlling & smoothing the player movement
  /*
   * dir holds the actual angle of the direction where top is 0 degrees
   * localRadius restricts the movement around the sphere
   * retSteps used for speed calculations
   * ud/lr hold the movement direction coordinates
   */
  static float dir;
  const float localRadius = 0.5f;
  const int retSteps = 25;
  const int angleStep = 8;
  float ud = 0, lr = 0;
  float xDest, xMove;
  float yDest, yMove;

  m_turn = 0;

  // Using the cross product we calculate the new up and side vectors for the camera
  // to control the correct movement of the camera and the player
  io_cam.m_eye.normalize();

  io_cam.m_w = io_cam.m_eye;
  io_cam.m_w = io_cam.m_w.cross(io_cam.m_up);
  io_cam.m_up = io_cam.m_w.cross(io_cam.m_eye);
  io_cam.m_w.normalize();
  io_cam.m_up.normalize();

  /*
   * Handle keyboard direction (trying to imitate controller stick coordinates)
   * Y-axis (U/D):
   * Top: 1
   * Top left/right: sin(45)
   * Bottom: -1
   * Bottom left/right: -sin(45)
   *
   * X-axis (L/R):
   * Left: -1
   * Left top/bottom: -sin(45)
   * Right: 1
   * Right top/bottom: sin(45)
   */
  if(_c != NULL)
  {
    ud = -SDL_GameControllerGetAxis(_c, SDL_CONTROLLER_AXIS_LEFTY);
    lr = SDL_GameControllerGetAxis(_c, SDL_CONTROLLER_AXIS_LEFTX);

    // As the controller sticks X360 gets it's values between -32768.0 to 32767.0 (signed int)
    // We're checking whether it surpasses the sensitivity threshold and then normalising it
    ud = (fabs(ud) < sensitivity ? 0 : ud/32767.0);
    lr = (fabs(lr) < sensitivity ? 0 : lr/32767.0);
  }
  else
  {
    if(keystate[SDL_SCANCODE_W])
      ud = (keystate[SDL_SCANCODE_A] || keystate[SDL_SCANCODE_D] ? sinf(PI4) : 1);
    else if(keystate[SDL_SCANCODE_S])
      ud = (keystate[SDL_SCANCODE_A] || keystate[SDL_SCANCODE_D] ? -sinf(PI4) : -1);

    if(keystate[SDL_SCANCODE_A])
      lr = (keystate[SDL_SCANCODE_W] || keystate[SDL_SCANCODE_S] ? -sinf(PI4) : -1);
    else if(keystate[SDL_SCANCODE_D])
      lr = (keystate[SDL_SCANCODE_W] || keystate[SDL_SCANCODE_S] ? sinf(PI4) : 1);
  }

  // Calculate the player movement "inside a circle" in front of the camera
  // This is then used to simulate the camera trying to catch up
  xDest = sinf(atan2f(lr, ud)) * localRadius;
  yDest = sinf(atan2f(ud, lr)) * localRadius;
  yMove = (yDest - m_yMov)/(float)retSteps;
  xMove = (xDest - m_xMov)/(float)retSteps;

  // Adding the movement to the variables that are used to translate the player
  // We're recalculating the yMove and xMove each frame to have the movement
  // smooth to the end, thus camera catches up.
  m_yMov = (m_yMov > yDest ? m_yMov + yMove :
          (m_yMov < yDest ? m_yMov + yMove : m_yMov));
  m_xMov = (m_xMov > xDest ? m_xMov + xMove :
          (m_xMov < xDest ? m_xMov + xMove : m_xMov));

  // Move the camera to the direction of the up and the left vector
  // based on the player's desired direction
  // Also when check whether the player's smoothing towards the center is happening
  // and smooth the camera's movement as well
  if(ud)
  {
    io_cam.m_eye.m_x += ud * io_cam.m_up.m_x * MOVESPEED;
    io_cam.m_eye.m_y += ud * io_cam.m_up.m_y * MOVESPEED;
    io_cam.m_eye.m_z += ud * io_cam.m_up.m_z * MOVESPEED;
  }
  else
  {
    io_cam.m_eye.m_x -= io_cam.m_up.m_x * yMove;
    io_cam.m_eye.m_y -= io_cam.m_up.m_y * yMove;
    io_cam.m_eye.m_z -= io_cam.m_up.m_z * yMove;
  }
  if(lr)
  {
    io_cam.m_eye.m_x -= lr * io_cam.m_w.m_x * MOVESPEED;
    io_cam.m_eye.m_y -= lr * io_cam.m_w.m_y * MOVESPEED;
    io_cam.m_eye.m_z -= lr * io_cam.m_w.m_z * MOVESPEED;
  }
  else
  {
    io_cam.m_eye.m_x += io_cam.m_w.m_x * xMove;
    io_cam.m_eye.m_y += io_cam.m_w.m_y * xMove;
    io_cam.m_eye.m_z += io_cam.m_w.m_z * xMove;
  }

  io_cam.m_eye.normalize();

  io_cam.m_eye *= CAMRADIUS;
  m_pos = io_cam.m_eye;

  // Get the cameras matrix to be used to orient the player as well
  m_orientation = GLFunctions::orientation(io_cam.m_eye, io_cam.m_look, io_cam.m_up);

  // Check whether player is moving somewhere and
  // handle the possible rotation and tilting
  if(ud != 0 || lr != 0)
  {
    // Map the ud & lr coords to angles and substract 90 degrees to have top be 0
    dir = atan2f(ud, lr) * 180/PI - 90;
    wrapRotation(dir);

    // Calculate how far away the ships current rotation is from the desired one
    float distance = dir - m_rot;
    float aStep = angleStep;

    // Used to smooth the rotation as well
    if(fabs(distance) < angleStep)
      aStep = fabs(distance);

    // Calculating the rotation for the ship
    m_rot = ((distance > 0 && distance <= 180) || distance < -180 ? m_rot + aStep :
          ((distance >= -180 && distance < 0) || distance > 180 ? m_rot - aStep : m_rot));

    // Calculating the tilt for the ship
    m_turn = ((distance > 0 && distance <= 180) || distance < -180 ? -25 :
          ((distance >= -180 && distance < 0) || distance > 180 ? 25 : 0));
  }

  // If the ship is moving we'll increse the volume of the background noise
  if(m_xMov || m_yMov)
    Mix_VolumeMusic(MIX_MAX_VOLUME * (((fabs(m_xMov) + fabs(m_yMov))/0.5f) < 0.25f ? 0.05f : ((fabs(m_xMov) + fabs(m_yMov))/0.5f)));

  // Wrap the rotation to be between 0 and 360
  wrapRotation(m_rot);

  // Call the shooting function with the controller and camera up and side vectors
  shoot(_c, io_cam.m_up, io_cam.m_w);
}
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------
void Player::shoot(
                   SDL_GameController *_c,
                   const Vec4 &_cu,
                   const Vec4 &_cl
                  )
{
  // Initially we're not shooting
  bool shoot = false;
  float x = 0, y = 0;

  // Using controller as the primary device
  if(_c != NULL)
  {
    // Get the controller right stick "action"
    x = SDL_GameControllerGetAxis(_c, SDL_CONTROLLER_AXIS_RIGHTX);
    y = -SDL_GameControllerGetAxis(_c, SDL_CONTROLLER_AXIS_RIGHTY);

    x = (fabs(x) < sensitivity ? 0 : x/32767.0);
    y = (fabs(y) < sensitivity ? 0 : y/32767.0);

    // If the right stick movement surpasses the sensitivity threshold we're shooting
    if(x != 0 || y != 0)
      shoot = true;
  }
  else
  {
    const Uint8 *keystate = SDL_GetKeyboardState(NULL);

    // Get the aim direction from the keyboard
    m_aimDir = fmod((keystate[SDL_SCANCODE_LEFT] ? m_aimDir + 0.1f :
             (keystate[SDL_SCANCODE_RIGHT] ? m_aimDir - 0.1f : m_aimDir)), TWO_PI);

    if(keystate[SDL_SCANCODE_SPACE])
      shoot = true;
  }

  if((x != 0 || y != 0) && _c)
    m_aimDir = atan2f(y, x);

  // If the player's shooting we'll be creating projectiles inside this statement
  if(shoot)
  {

    /*if(!Mix_Playing(1))
    {
      if(Mix_PlayChannel(1, a_fire, -1) == -1)
          std::cerr << "Unable to play WAV file: " << Mix_GetError() << "\n";
    }
    if(Mix_Paused(1))
      Mix_Resume(1);*/

    Vec4 n = m_pos;
    n.normalize();

    // Pushing projectile and setting the starting position of the projectile to be where ever
    // the player is at the moment and giving it a random lifetime
    m_p.push_back(Projectile(n.m_x * (WORLDRADIUS + PLAYEROFFSET) + (m_xMov * -_cl.m_x + m_yMov * _cu.m_x),
                             n.m_y * (WORLDRADIUS + PLAYEROFFSET) + (m_xMov * -_cl.m_y + m_yMov * _cu.m_y),
                             n.m_z * (WORLDRADIUS + PLAYEROFFSET) + (m_xMov * -_cl.m_z + m_yMov * _cu.m_z),
                             _cu, _cl,
                             n.m_x, n.m_y, n.m_z,
                             m_aimDir, std::rand()%30 + 25));
  }

  // Looping through the projectile vector and drawing them, could be set into a separate function
  glBindTexture(GL_TEXTURE_2D, m_projectileId);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE);

  // Disable depth mask so the points above won't occlude the ones behind
  glDepthMask(GL_FALSE);

    glBegin(GL_TRIANGLES);
      for(int i = 0; i < (int)m_p.size(); ++i)
      {
        m_p[i].drawProjectile(3, _cu, _cl);
        if(m_p[i].m_life == m_p[i].m_maxLife)
          m_p.erase(m_p.begin() + i);
      }
    glEnd();

  glBindTexture(GL_TEXTURE_2D, 0);

  // Enable depth mask after the points are drawn so nothing else is affected
  glDepthMask(GL_TRUE);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------
void Player::ship()
{
  // Generates the displaylist from the ship model
  GLuint id = glGenLists(1);
  glNewList(id, GL_COMPILE);

    glRotatef(90, 1, 0, 0);

    glScalef(0.02f, 0.02f, 0.02f);

    glColor3f(1.0f, 1.0f, 1.0f);
    glBindTexture(GL_TEXTURE_2D, m_shipTexId);

    glBegin(GL_TRIANGLES);
      for(int i = 0; i < (int)m_ship.m_Ind.size(); i += 3)
      {
        m_ship.m_Norms[m_ship.m_Ind[i + 2] - 1].normalGL();
        m_ship.m_Text[m_ship.m_Ind[i + 1] - 1].textureGL();
        m_ship.m_Verts[m_ship.m_Ind[i] - 1].vertexGL();
      }
    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);
    glScalef(1.0f/0.02f, 1.0f/0.02f, 1.0f/0.02f);
  glEndList();
  m_displayList.push_back(id);
}
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------
void Player::wrapRotation(
                          float &io_a
                         )
{
  if(io_a < 0)
    io_a = 360 - fabs(fmod(io_a, 360));
  else
    io_a = fmod(io_a, 360);
}
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------
void Player::checkCollisions(
                             std::vector<Asteroid> &io_a,
                             std::list<int> &io_aInd
                            )
{
  float dist;
  int extra_particles = 0;

  // A bit of a hacky solution, here we calculate the position of the player
  // if the ship would be located on the surface of the atmosphere, thus
  // collision checking will be easier as the asteroid is considered to hit
  // the player when the player gets under one.
  Vec4 paDist = m_pos + Vec4(m_orientation.m_00 * m_xMov + m_orientation.m_01 * m_yMov,
                             m_orientation.m_10 * m_xMov + m_orientation.m_11 * m_yMov,
                             m_orientation.m_20 * m_xMov + m_orientation.m_21 * m_yMov);
  paDist.normalize();
  paDist *= WORLDRADIUS*ASPHERERADIUS;

  // Iterator to iterate through the asteroids that have reached the atmosphere
  std::list<int>::iterator it = io_aInd.begin();

  for(it; it != io_aInd.end(); ++it)
  {
    // Looping through all the living projectiles
    for(int i = 0; i < (int)m_p.size(); ++i)
    {
      // Get the distance between a projectile and an asteroid
      dist = (io_a[*it].m_pos - m_p[i].m_pos).length();

      // Checks if the distance from the origin of the asteroid is small enough
      // then we have a collision
      if(dist < io_a[*it].m_size * 0.75f)
      {
        // Decrease the life of the asteroid and increase the players score
        io_a[*it].m_life -= 6;
        ++m_score;

        // If the asteroid was destroyed, we increase the amount of fire particles
        // it spawns to give more of an explosion effect
        if(io_a[*it].m_life <= 0)
          extra_particles = 50;

        // Spawn fire particles whenever an asteroid gets hit
        for(int j = 0; j < FIRE_PARTICLES + extra_particles; ++j)
          m_particles.push_back(Particle(m_p[i].m_pos, 25));

        // Destroy the projectile that hit the asteroid
        m_p.erase(m_p.begin() + i);
      }
    }

    // Checks for a collision between the player and an asteroid
    if((io_a[*it].m_pos - paDist).length() <= io_a[*it].m_size * 0.5)
    {
      m_life -= 20;
      // If the player dies (life reaches 0 or below), we spawn fire particles
      // to the position of the player
      if(m_life <= 0)
      {
        for(int j = 0; j < 250; ++j)
          m_particles.push_back(Particle(m_pos, 50));
      }
    }
  }
}
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------
void Player::drawParticles()
{
  // Loop through the fire particles and draw them, for the fire particles we use a
  // kind of a flame sprite, combined with glBlendFunc (more intense parts become white)
  // And we disable the depthmask to display the particles that get drawn and left below
  // other particles
  glBlendFunc(GL_SRC_ALPHA, GL_ONE);
  glDepthMask(GL_FALSE);

  // To be able to render texture on GL_POINTS we're enabling point sprites and setting
  // the texture environment flags to map the textures to a point
  glBindTexture(GL_TEXTURE_2D, m_particleTexId);
  glTexEnvi(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE);

  glPointSize(50);
  glBegin(GL_POINTS);
    for(int i = 0; i < (int)m_particles.size(); ++i)
    {
      m_particles[i].draw();
      m_particles[i].move();
      ++m_particles[i].m_life;
      if(m_particles[i].m_life >= m_particles[i].m_max_life)
        m_particles.erase(m_particles.begin() + i);
    }
  glEnd();

  // When the drawing is finished we return all the set flags to normal
  glBindTexture(GL_TEXTURE_2D, 0);
  glDepthMask(GL_TRUE);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
// ---------------------------------------------------------------------------------------
