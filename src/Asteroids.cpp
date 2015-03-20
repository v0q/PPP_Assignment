#include <OpenGL/gl.h>
#include <iostream>

#include "Asteroids.h"

void Asteroid::draw()
{
  float r = 0.05f*size;
  move();
  glPushMatrix();
    glTranslatef(pos.m_x, pos.m_y, pos.m_z);
    glRotatef(rot, 1, 1, 1);
    glBegin(GL_TRIANGLES);
      glColor3f(0, 0, 1);

      // Side 1
      glNormal3f(0, 0, 1);
      glVertex3f(r, r, r);
      glVertex3f(-r, r, r);
      glVertex3f(r, -r, r);

      glVertex3f(-r, r, r);
      glVertex3f(-r, -r, r);
      glVertex3f(r, -r, r);

      // Side 2
      glNormal3f(0, 0, -1);
      glVertex3f(r, r, -r);
      glVertex3f(r, -r, -r);
      glVertex3f(-r, r, -r);

      glVertex3f(-r, r, -r);
      glVertex3f(r, -r, -r);
      glVertex3f(-r, -r, -r);

      // Side 3
      glNormal3f(-1, 0, 0);
      glVertex3f(-r, r, -r);
      glVertex3f(-r, -r, -r);
      glVertex3f(-r, r, r);

      glVertex3f(-r, r, r);
      glVertex3f(-r, -r, -r);
      glVertex3f(-r, -r, r);

      // Side 4
      glNormal3f(1, 0, 0);
      glVertex3f(r, r, -r);
      glVertex3f(r, r, r);
      glVertex3f(r, -r, -r);

      glVertex3f(r, r, r);
      glVertex3f(r, -r, r);
      glVertex3f(r, -r, -r);

      // Side 5
      glNormal3f(0, 1, 0);
      glVertex3f(-r, r, -r);
      glVertex3f(-r, r, r);
      glVertex3f(r, r, -r);

      glVertex3f(-r, r, r);
      glVertex3f(r, r, r);
      glVertex3f(r, r, -r);

      // Side 6
      glNormal3f(0, -1, 0);
      glVertex3f(-r, -r, -r);
      glVertex3f(r, -r, -r);
      glVertex3f(-r, -r, r);

      glVertex3f(-r, -r, r);
      glVertex3f(r, -r, -r);
      glVertex3f(r, -r, r);
    glEnd();
  glPopMatrix();
}

void Asteroid::move()
{
  if(pos.length() > WORLDRADIUS*ASPHERERADIUS)
  {
    pos += dir*speed;
    rot += 5;
  }
  else if(speed != 0)
  {
    // When the asteroid hits the atmosphere reduce the speed to 0 for now
    speed = 0;
    pos.normalize();
    pos *= WORLDRADIUS*ASPHERERADIUS;
  }
  else
    ++rot;
}
