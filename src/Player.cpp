#include <OpenGl/gl.h>
#include <iostream>
#include <SDL.h>
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

void Player::handleMovement()
{
  const Uint8 *keystate = SDL_GetKeyboardState(NULL);

  // Variables for controlling & smoothing the player movement
  static float i = 100.0f, j = 100.0f;
  static float dir;
  const int localRadius = 12;
  const int retSteps = 25;
  const int angleStep = 8;
  float iReturn = fabs((i - 100) / (float)retSteps);
  float jReturn = fabs((j - 100) / (float)retSteps);
  float iMoveP = (localRadius - (i - 100)) / (float)retSteps;
  float jMoveP = (localRadius - (j - 100)) / (float)retSteps;
  float iMoveN = (localRadius - (100 - i)) / (float)retSteps;
  float jMoveN = (localRadius - (100 - j)) / (float)retSteps;
  float ud = 0, lr = 0;

  if(keystate[SDL_SCANCODE_UP])
  {
    ud = 1;
    i = (i - 100 < localRadius ? i + iMoveP : i);
    //rot = (rot > 0 && rot <= 180 ? rot - 10 :
    //      (rot > 180 && rot < 360 ? rot + 10 : 0));
  }
  else if(keystate[SDL_SCANCODE_DOWN])
  {
    ud = -1;
    i = (100 - i < localRadius ? i - iMoveN : i);
    //rot = (rot >= 0 && rot < 180 ? rot + 10 :
    //      (rot > 180 && rot < 360 ? rot - 10 : 180));
  }

  if(keystate[SDL_SCANCODE_LEFT])
  {
    lr = 1;
    j = (j - 100 < localRadius ? j + jMoveP : j);
    //rot = (rot >= 270 || (rot >= 0 && rot < 90) ? rot + 10 :
    //      (rot < 270 && rot > 90 ? rot - 10 : 90));
  }
  else if(keystate[SDL_SCANCODE_RIGHT])
  {
    lr = -1;
    j = (100 - j < localRadius ? j - jMoveN : j);
    //rot = (rot <= 90 || rot > 270 ? rot - 10 :
    //      rot >90 && rot < 270 ? rot + 10 : 270);
  }

  if(!keystate[SDL_SCANCODE_UP] && !keystate[SDL_SCANCODE_DOWN])
  {
    if(i > 100.25f)
    {
      i -= iReturn;
      //io_world.rotX = fmod((io_world.rotX - (i - 100) / (float)retSteps), 360);
    }
    else if(i < 99.75f)
    {
      i += iReturn;
      //io_world.rotX = fmod((io_world.rotX + (100 - i) / (float)retSteps), 360);
    }
    else
      i = 100.0f;
  }

  if(!keystate[SDL_SCANCODE_LEFT] && !keystate[SDL_SCANCODE_RIGHT])
  {
    if(j > 100.25f)
    {
      j -= jReturn;
      //io_world.rotY = fmod((io_world.rotY - jReturn), 360);
    }
    else if(j < 99.75f)
    {
      j += jReturn;
      //io_world.rotY = fmod((io_world.rotY + jReturn), 360);
    }
    else
      j = 100.0f;
  }

  // Check whether player is moving somewhere and
  // handle the possible rotation required
  if(ud != 0 || lr != 0)
  {
    float urd = (ud == 0 ? 0 : acosf(ud) * 180/PI);
    float lrd = fabs(asinf(lr) * 180/PI);
    dir = (lr >= 0 ? (urd + lrd) / (abs(ud) + abs(lr)) :
          -(urd + lrd) / (abs(ud) + abs(lr)));

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
  pos = Vec4::sphericalCoords(i, j, PLAYEROFFSET, 1);
  norm = Vec4::sphericalCoords(i, j, PLAYEROFFSET, 0);
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

