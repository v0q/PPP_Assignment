#include <iostream>

#include "Asteroids.h"

void Asteroid::draw(std::vector<GLuint> &_dL)
{
  move();
  glPushMatrix();

    glTranslatef(pos.m_x, pos.m_y, pos.m_z);
    glScalef(size, size, size);
    glRotatef(rot, 1, 1, 1);

    glColor4f(1, 1, 1, 1);
    glCallList(_dL[aType]);

  glPopMatrix();
}

void Asteroid::move()
{
  if(pos.length() > WORLDRADIUS*ASPHERERADIUS && speed > 0.031f)
  {
    pos += dir*speed;
    rot += 5;
  }
  else
  {
    speed = 0.03f;

    pos.normalize();
    side = pos.cross(up);
    side.normalize();
    pos *= WORLDRADIUS*ASPHERERADIUS;

    pos.m_x += speed * side.m_x;
    pos.m_y += speed * side.m_y;
    pos.m_z += speed * side.m_z;

    ++rot;
  }
}
