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
    glColor3f(1.0f, 0.0f, 0.0f);
    glPointSize(25.0f);

    glBegin(GL_POINTS);
      pos.vertexGL();
    glEnd();

    glBegin(GL_LINE_STRIP);
      pos.vertexGL();
      pos.vertexGL();
    glEnd();
  glPopMatrix();
}
