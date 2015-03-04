#include <OpenGl/gl.h>
#include <iostream>
#include "Player.h"
#include "Defs.h"
#include "World.h"

Player::~Player()
{

}

void Player::drawPlayer()
{
  glPushMatrix();
    glColor3f(1.0f, 0.0, 0.0f);
    glPointSize(15.0f);

    // Move player to the correct position and rotate
    glTranslatef(pos.m_x, pos.m_y, pos.m_z);
    glRotatef(rot, 0, 0, 1);

    cube();

  glPopMatrix();
}

void Player::handleMovement_kb()
{
  const Uint8 *keystate = SDL_GetKeyboardState(NULL);

  // Variables for controlling & smoothing the player movement
  /*
   * i and j are used to calculate the player coordinates around the sphere
   * dir holds the actual angle of the direction where top is 0 degrees
   * localRadius restricts the movement around the sphere
   * retSteps used for speed calculations
   * ..Return gives the return speed
   * ..Move gives the movement speed
   * ud/lr hold the movement direction coordinates
   */
  static float i = 99.0f, j = 100.0f;
  static float dir;
  const int localRadius = 12;
  const int retSteps = 25;
  const int angleStep = 8;
  float iReturn = fabs((i - 99) / (float)retSteps);
  float jReturn = fabs((j - 100) / (float)retSteps);
  float iMoveP = (localRadius - (i - 99)) / (float)retSteps;
  float jMoveP = (localRadius - (j - 100)) / (float)retSteps;
  float iMoveN = (localRadius - (99 - i)) / (float)retSteps;
  float jMoveN = (localRadius - (100 - j)) / (float)retSteps;
  float ud = 0, lr = 0;

  /*
   * Handle keyboard direction (trying to imitate controller stick coordinates
   * Y-axis (U/D):
   * Top: 1
   * Top left/right: 0.5
   * Bottom: -1
   * Bottom left/right: 0.5
   *
   * X-axis (L/R):
   * Left: -1
   * Left top/bottom: -0.5
   * Right: 1
   * Right top/bottom: 0.5
   */
  if(keystate[SDL_SCANCODE_UP])
  {
    ud = (keystate[SDL_SCANCODE_LEFT] || keystate[SDL_SCANCODE_RIGHT] ? 0.5 : 1);
    i = (i - 99 < localRadius ? i + iMoveP : i);
  }
  else if(keystate[SDL_SCANCODE_DOWN])
  {
    ud = (keystate[SDL_SCANCODE_LEFT] || keystate[SDL_SCANCODE_RIGHT] ? -0.5 : -1);
    i = (99 - i < localRadius ? i - iMoveN : i);
  }

  if(keystate[SDL_SCANCODE_LEFT])
  {
    lr = (keystate[SDL_SCANCODE_UP] || keystate[SDL_SCANCODE_DOWN] ? -0.5 : -1);
    j = (j - 100 < localRadius ? j + jMoveP : j);
  }
  else if(keystate[SDL_SCANCODE_RIGHT])
  {
    lr = (keystate[SDL_SCANCODE_UP] || keystate[SDL_SCANCODE_DOWN] ? 0.5 : 1);
    j = (100 - j < localRadius ? j - jMoveN : j);
  }

  if(!keystate[SDL_SCANCODE_UP] && !keystate[SDL_SCANCODE_DOWN])
  {
    if(i > 99.25f)
    {
      i -= iReturn;
    }
    else if(i < 98.75f)
    {
      i += iReturn;
    }
    else
      i = 99.0f;
  }

  if(!keystate[SDL_SCANCODE_LEFT] && !keystate[SDL_SCANCODE_RIGHT])
  {
    if(j > 100.25f)
    {
      j -= jReturn;
    }
    else if(j < 99.75f)
    {
      j += jReturn;
    }
    else
      j = 100.0f;
  }

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
  }

  wrapRotation(rot);

  // Get the players coordinates and normal on the surface of the sphere
  norm = pos = Vec4::sphericalCoords(i, j, PLAYEROFFSET);
  norm.normalize();

}

void Player::handleMovement_c(SDL_GameController *_c)
{
  // Variables for controlling & smoothing the player movement
  static float i = 99.0f, j = 100.0f;
  static float dir;
  const int localRadius = 12;
  const int retSteps = 25;
  const int angleStep = 8;
  float iReturn = fabs((i - 99) / (float)retSteps);
  float jReturn = fabs((j - 100) / (float)retSteps);
  float iMoveP = (localRadius - (i - 99)) / (float)retSteps;
  float jMoveP = (localRadius - (j - 100)) / (float)retSteps;
  float iMoveN = (localRadius - (99 - i)) / (float)retSteps;
  float jMoveN = (localRadius - (100 - j)) / (float)retSteps;
  float ud = -SDL_GameControllerGetAxis(_c, SDL_CONTROLLER_AXIS_LEFTY);
  float lr = SDL_GameControllerGetAxis(_c, SDL_CONTROLLER_AXIS_LEFTX);

  ud = (fabs(ud) < sensitivity ? 0 : ud/32767.0);
  lr = (fabs(lr) < sensitivity ? 0 : lr/32767.0);

  if(ud > 0)
    i = (i - 99 < localRadius ? i + iMoveP : i);
  else if(ud < 0)
    i = (99 - i < localRadius ? i - iMoveN : i);

  if(lr < 0)
    j = (j - 100 < localRadius ? j + jMoveP : j);
  else if(lr > 0)
    j = (100 - j < localRadius ? j - jMoveN : j);

  if(!ud)
  {
    if(i > 99.25f)
    {
      i -= iReturn;
    }
    else if(i < 98.75f)
    {
      i += iReturn;
    }
    else
      i = 99.0f;
  }

  if(!lr)
  {
    if(j > 100.25f)
    {
      j -= jReturn;
    }
    else if(j < 99.75f)
    {
      j += jReturn;
    }
    else
      j = 100.0f;
  }

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
  }

  wrapRotation(rot);

  // Get the players coordinates and normal on the surface of the sphere
  norm = pos = Vec4::sphericalCoords(i, j, PLAYEROFFSET);
  norm.normalize();
}

void Player::cube()
{
  float r = 0.05f;

  glBegin(GL_QUADS);
    norm.normalGL();
    // Side 1
    glVertex3f(-r, r, r/2);
    glVertex3f(r, r, r/2);
    glVertex3f(r, -r, r/2);
    glVertex3f(-r, -r, r/2);

    // Side 2
    glVertex3f(-r, r, -r/2);
    glVertex3f(r, r, -r/2);
    glVertex3f(r, -r, -r/2);
    glVertex3f(-r, -r, -r/2);

    // Side 3
    glVertex3f(-r, r, r/2);
    glVertex3f(-r, r, -r/2);
    glVertex3f(-r, -r, -r/2);
    glVertex3f(-r, -r, r/2);

    // Side 4
    glVertex3f(r, r, r/2);
    glVertex3f(r, r, -r/2);
    glVertex3f(r, -r, -r/2);
    glVertex3f(r, -r, r/2);

    // Side 5
    glVertex3f(-r, r, r/2);
    glVertex3f(-r, r, -r/2);
    glVertex3f(r, r, -r/2);
    glVertex3f(r, r, r/2);

    // Side 6
    glVertex3f(-r, -r, r/2);
    glVertex3f(-r, -r, -r/2);
    glVertex3f(r, -r, -r/2);
    glVertex3f(r, -r, r/2);

  glEnd();
  glBegin(GL_LINE_STRIP);
    glColor3f(1,0,0);
    glVertex3f(0,0,0);
    glVertex3f(0,1,0);
  glEnd();
}

void Player::wrapRotation(float &io_a)
{
  if(io_a < 0)
    io_a = 360 - fabs(fmod(io_a, 360));
  else
    io_a = fmod(io_a, 360);
}

