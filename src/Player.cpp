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

Player::Player(float _x, float _y, float _z) : score(0), pos(_x, _y, _z, 1.0f), aimDir(0.0f), rot(0.0f), turn(0.0f), xMov(0.0f), yMov(0.0f), life(100)
{
  loadModel("models/ss.obj", m_ship);
  ship();

  loadTexture("textures/projectile4.png", particleTexId);
  loadTexture("textures/animated_explosion.png", projectileId);
  loadTexture("textures/ss_texture.png", shipTexId);

  audio::loadSound("sounds/flame.wav", &a_fire);
  audio::loadSound("sounds/bg_sound.ogg", &bgSound);
  Mix_PlayMusic(bgSound, -1); Mix_VolumeMusic(MIX_MAX_VOLUME * 0.05f);
}

Player::~Player()
{
  p.clear();
  std::vector<Projectile>().swap(p);
  particles.clear();
  std::vector<Particle>().swap(particles);

  freeModelMem(m_ship);

  Mix_FreeChunk(a_fire);
  Mix_FreeMusic(bgSound);
}

bool Player::isAlive()
{
  if(life > 0)
    return true;
  else
    return false;
}

void Player::drawPlayer()
{
    glMultMatrixf(orientation.m_openGL);
    glLoadIdentity();

    glPointSize(15.0f);

    // Move player to the correct position
    glTranslatef(xMov, yMov, -pos.length()+WORLDRADIUS+PLAYEROFFSET);

    glBegin(GL_POINTS);
      glColor3f(0, 0, 0);
      glVertex3f(0.1*cosf(aimDir), 0.1*sinf(aimDir), 0);
    glEnd();

    glRotatef(rot, 0, 0, 1);
    glRotatef(turn, 0, 1, 0);

    glColor3f(1.0f, 0.0, 0.0f);
    glCallLists(m_displayList.size(), GL_UNSIGNED_INT, &m_displayList[0]);
}

void Player::handleMovement(SDL_GameController *_c, Camera &_cam)
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

  turn = 0;

  // Using the cross product we calculate the new up and side vectors for the camera
  // to control the correct movement of the camera and the player
  _cam.eye.normalize();

  _cam.w = _cam.eye;
  _cam.w = _cam.w.cross(_cam.up);
  _cam.up = _cam.w.cross(_cam.eye);
  _cam.w.normalize();
  _cam.up.normalize();

  /*
   * Handle keyboard direction (trying to imitate controller stick coordinates
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

  // Calculate the player movement "inside a circle"
  // in front of the camera
  xDest = sinf(atan2f(lr, ud)) * localRadius;
  yDest = sinf(atan2f(ud, lr)) * localRadius;
  yMove = (yDest - yMov)/(float)retSteps;
  xMove = (xDest - xMov)/(float)retSteps;

  yMov = (yMov > yDest ? yMov + yMove :
          (yMov < yDest ? yMov + yMove : yMov));
  xMov = (xMov > xDest ? xMov + xMove :
          (xMov < xDest ? xMov + xMove : xMov));

  // Move the camera to the direction of the up and the left vector
  // based on the player's desired direction
  // Also when check whether the player's smoothing towards the center is happening
  // and smooth the camera's movement as well
  if(ud)
  {
    _cam.eye.m_x += ud * _cam.up.m_x * MOVESPEED;
    _cam.eye.m_y += ud * _cam.up.m_y * MOVESPEED;
    _cam.eye.m_z += ud * _cam.up.m_z * MOVESPEED;
  }
  else
  {
    _cam.eye.m_x -= _cam.up.m_x * yMove;
    _cam.eye.m_y -= _cam.up.m_y * yMove;
    _cam.eye.m_z -= _cam.up.m_z * yMove;
  }
  if(lr)
  {
    _cam.eye.m_x -= lr * _cam.w.m_x * MOVESPEED;
    _cam.eye.m_y -= lr * _cam.w.m_y * MOVESPEED;
    _cam.eye.m_z -= lr * _cam.w.m_z * MOVESPEED;
  }
  else
  {
    _cam.eye.m_x += _cam.w.m_x * xMove;
    _cam.eye.m_y += _cam.w.m_y * xMove;
    _cam.eye.m_z += _cam.w.m_z * xMove;
  }

  _cam.eye.normalize();

  _cam.eye *= CAMRADIUS;
  pos = _cam.eye;

  orientation = GLFunctions::orientation(_cam.eye, _cam.look, _cam.up);

  // Check whether player is moving somewhere and
  // handle the possible rotation required
  if(ud != 0 || lr != 0)
  {
    // Map the ud & lr coords to angles and substract 90 degrees to have top be 0
    dir = atan2f(ud, lr) * 180/PI - 90;
    wrapRotation(dir);

    float distance = dir - rot;
    float aStep = angleStep;
    if(fabs(distance) < angleStep)
      aStep = fabs(distance);
    rot = ((distance > 0 && distance <= 180) || distance < -180 ? rot + aStep :
          ((distance >= -180 && distance < 0) || distance > 180 ? rot - aStep : rot));
    turn = ((distance > 0 && distance <= 180) || distance < -180 ? -25 :
          ((distance >= -180 && distance < 0) || distance > 180 ? 25 : 0));
  }

  if(xMov || yMov)
    Mix_VolumeMusic(MIX_MAX_VOLUME * (((fabs(xMov) + fabs(yMov))/0.5f) < 0.25f ? 0.05f : ((fabs(xMov) + fabs(yMov))/0.5f)));

  wrapRotation(rot);

  shoot(_c, _cam.up, _cam.w);
}

void Player::shoot(SDL_GameController *_c, Vec4 &_cu, Vec4 &_cl)
{
  bool shoot = false;
  float x = 0, y = 0;

  if(_c != NULL)
  {
    x = SDL_GameControllerGetAxis(_c, SDL_CONTROLLER_AXIS_RIGHTX);
    y = -SDL_GameControllerGetAxis(_c, SDL_CONTROLLER_AXIS_RIGHTY);

    x = (fabs(x) < sensitivity ? 0 : x/32767.0);
    y = (fabs(y) < sensitivity ? 0 : y/32767.0);

    if(x != 0 || y != 0)
      shoot = true;
  }
  else
  {
    const Uint8 *keystate = SDL_GetKeyboardState(NULL);

    aimDir = fmod((keystate[SDL_SCANCODE_LEFT] ? aimDir + 0.1f :
             (keystate[SDL_SCANCODE_RIGHT] ? aimDir - 0.1f : aimDir)), TWO_PI);

    if(keystate[SDL_SCANCODE_SPACE])
      shoot = true;
  }

  if((x != 0 || y != 0) && _c)
    aimDir = atan2f(y, x);

  if(shoot)
  {
    /*if(!Mix_Playing(1))
    {
      if(Mix_PlayChannel(1, a_fire, -1) == -1)
          std::cerr << "Unable to play WAV file: " << Mix_GetError() << "\n";
    }
    if(Mix_Paused(1))
      Mix_Resume(1);*/

    Vec4 n = pos;
    n.normalize();

    for(int i = 0; i < 3; ++i)
    {
      p.push_back(Projectile(n.m_x * (WORLDRADIUS + PLAYEROFFSET) + (xMov * -_cl.m_x + yMov * _cu.m_x),
                             n.m_y * (WORLDRADIUS + PLAYEROFFSET) + (xMov * -_cl.m_y + yMov * _cu.m_y),
                             n.m_z * (WORLDRADIUS + PLAYEROFFSET) + (xMov * -_cl.m_z + yMov * _cu.m_z),
                             _cu, _cl,
                             n.m_x, n.m_y, n.m_z,
                             aimDir, std::rand()%30 + 25));
    }
  }

  glBindTexture(GL_TEXTURE_2D, projectileId);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE);

  // Disable depth mask so the points above won't occlude the ones behind
  glDepthMask(GL_FALSE);

    glBegin(GL_TRIANGLES);
      for(int i = 0; i < (int)p.size(); ++i)
      {
        p[i].drawProjectile(3, _cu, _cl);
        if(p[i].life == p[i].max_life)
          p.erase(p.begin() + i);
      }
    glEnd();

  glBindTexture(GL_TEXTURE_2D, 0);

  // Enable depth mask after the points are drawn so nothing else is affected
  glDepthMask(GL_TRUE);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Player::ship()
{
  GLuint id = glGenLists(1);
  glNewList(id, GL_COMPILE);

    glBegin(GL_LINE_STRIP);
      glColor3f(1,0,0);
      glVertex3f(0,0,0);
      glVertex3f(0,1,0);
    glEnd();

    glRotatef(90, 1, 0, 0);
    glScalef(0.02, 0.02, 0.02);

    glColor3f(1.0f, 1.0f, 1.0f);
    glBindTexture(GL_TEXTURE_2D, shipTexId);
    std::cout << (int)m_ship.Verts.size() << "\n";

    glBegin(GL_TRIANGLES);
      for(int i = 0; i < (int)m_ship.Ind.size(); i += 3)
      {
        m_ship.Norms[m_ship.Ind[i + 2] - 1].normalGL();
        m_ship.Text[m_ship.Ind[i + 1] - 1].textureGL();
        m_ship.Verts[m_ship.Ind[i] - 1].vertexGL();
      }
    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);
  glEndList();
  m_displayList.push_back(id);
}

void Player::wrapRotation(float &io_a)
{
  if(io_a < 0)
    io_a = 360 - fabs(fmod(io_a, 360));
  else
    io_a = fmod(io_a, 360);
}

void Player::checkCollisions(std::vector<Asteroid> &io_a, std::list<int> &io_aInd)
{
  float dist;
  int extra_particles = 0;
  Vec4 paDist = pos + Vec4(orientation.m_00*xMov + orientation.m_01*yMov,
                           orientation.m_10*xMov + orientation.m_11*yMov,
                           orientation.m_20*xMov + orientation.m_21*yMov);
  paDist.normalize();
  paDist *= WORLDRADIUS*ASPHERERADIUS;

  std::list<int>::iterator it = io_aInd.begin();

  for(it; it != io_aInd.end(); ++it)
  {
    for(int i = 0; i < (int)p.size(); ++i)
    {
      dist = (io_a[*it].pos - p[i].pos).length();
      if(dist < io_a[*it].size * 0.75f)
      {
        io_a[*it].life -= 2;
        ++score;

        if(io_a[*it].life <= 0)
          extra_particles = 50;

        for(int j = 0; j < max_particles + extra_particles; ++j)
          particles.push_back(Particle(p[i].pos, 25));

        p.erase(p.begin() + i);
      }
    }

    if((io_a[*it].pos - paDist).length() <= io_a[*it].size * 0.5)
    {
      life -= 20;
      if(life <= 0)
      {
        for(int j = 0; j < 250; ++j)
          particles.push_back(Particle(pos, 50));
      }
    }
  }
}

void Player::drawParticles()
{
  glBlendFunc(GL_SRC_ALPHA, GL_ONE);
  glDepthMask(GL_FALSE);

  glBindTexture(GL_TEXTURE_2D, particleTexId);
  glEnable(GL_POINT_SPRITE);
  glTexEnvi(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE);

  glPointSize(50);
  glBegin(GL_POINTS);
    for(int i = 0; i < (int)particles.size(); ++i)
    {
      particles[i].draw();
      particles[i].move();
      ++particles[i].life;
      if(particles[i].life >= particles[i].max_life)
        particles.erase(particles.begin() + i);
    }
  glEnd();

  glBindTexture(GL_TEXTURE_2D, 0);
  glDepthMask(GL_TRUE);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
