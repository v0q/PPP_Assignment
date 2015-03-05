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
    ud = (keystate[SDL_SCANCODE_LEFT] || keystate[SDL_SCANCODE_RIGHT] ? 0.5 : 1);
  else if(keystate[SDL_SCANCODE_DOWN])
    ud = (keystate[SDL_SCANCODE_LEFT] || keystate[SDL_SCANCODE_RIGHT] ? -0.5 : -1);

  if(keystate[SDL_SCANCODE_LEFT])
    lr = (keystate[SDL_SCANCODE_UP] || keystate[SDL_SCANCODE_DOWN] ? -0.5 : -1);
  else if(keystate[SDL_SCANCODE_RIGHT])
    lr = (keystate[SDL_SCANCODE_UP] || keystate[SDL_SCANCODE_DOWN] ? 0.5 : 1);

  xDest = sinf(atan2f(lr, ud)) * localRadius;
  yDest = sinf(atan2f(ud,lr)) * localRadius;
  yMove = fabs(yDest - pos.m_y)/(float)retSteps;
  xMove = fabs(xDest - pos.m_x)/(float)retSteps;

  pos.m_y = (pos.m_y > yDest ? pos.m_y - yMove :
            (pos.m_y < yDest ? pos.m_y + yMove : pos.m_y));
  pos.m_x = (pos.m_x > xDest ? pos.m_x - xMove :
            (pos.m_x < xDest ? pos.m_x + xMove : pos.m_x));

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
}

void Player::handleMovement_c(SDL_GameController *_c)
{
  // Variables for controlling & smoothing the player movement
  static float dir;
  const float localRadius = 0.5f;
  const int retSteps = 25;
  const int angleStep = 8;
  float ud = -SDL_GameControllerGetAxis(_c, SDL_CONTROLLER_AXIS_LEFTY);
  float lr = SDL_GameControllerGetAxis(_c, SDL_CONTROLLER_AXIS_LEFTX);
  float xDest, xMove;
  float yDest, yMove;

  ud = (fabs(ud) < sensitivity ? 0 : ud/32767.0);
  lr = (fabs(lr) < sensitivity ? 0 : lr/32767.0);

  xDest = sinf(atan2f(lr, ud)) * localRadius;
  yDest = sinf(atan2f(ud,lr)) * localRadius;
  yMove = fabs(yDest - pos.m_y)/(float)retSteps;
  xMove = fabs(xDest - pos.m_x)/(float)retSteps;

  pos.m_y = (pos.m_y > yDest ? pos.m_y - yMove :
            (pos.m_y < yDest ? pos.m_y + yMove : pos.m_y));
  pos.m_x = (pos.m_x > xDest ? pos.m_x - xMove :
            (pos.m_x < xDest ? pos.m_x + xMove : pos.m_x));

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

