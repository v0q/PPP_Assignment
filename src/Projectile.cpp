#include <OpenGL/gl.h>
#include <cmath>
#include <iostream>

#include "Projectile.h"
#include "Defs.h"

void Projectile::drawProjectile(int num_it, Vec4 &_cu, Vec4 &_cl)
{
  float tDim = 1.0/5.0;
  int step = floor(life*25/max_life);

  float xMin = tDim * (step%5);
  float xMax = tDim * (step%5 + 1);
  float yMin = tDim * (step/5);
  float yMax = tDim * (step/5 + 1);

  for(int i = 0; i < num_it; ++i)
  {
    // Calculate multipliers for the left and the up vectors
    // i.e. how much to move on each vector in each frame
    float lMul = (PROJECTILESPEED * cosf(dir)) / num_it;
    float uMul = (PROJECTILESPEED * sinf(dir)) / num_it;

    pos.m_x -= lMul * left.m_x;
    pos.m_y -= lMul * left.m_y;
    pos.m_z -= lMul * left.m_z;

    pos.m_x += uMul * up.m_x;
    pos.m_y += uMul * up.m_y;
    pos.m_z += uMul * up.m_z;

    if(pos.length() < WORLDRADIUS*ASPHERERADIUS)
    {
      // While the projectiles are under the atmosphere we
      // move them upwards more rapidly
      pos += Vec4(normal.m_x, normal.m_y, normal.m_z)*PROJECTILESPEED / num_it;
    }

    // Check if the projectile has reached the atmosphere,
    // if so we'll calculte new up/left vectors for it to
    // bend around the atmosphere
    if(pos.length() > WORLDRADIUS*ASPHERERADIUS)
    {
      pos.normalize();
      left = pos.cross(up);
      up = left.cross(pos);
      left.normalize();
      up.normalize();
      pos *= WORLDRADIUS*ASPHERERADIUS;
    }

    normal.normalGL();
    glColor4f(1,
              1 - (life / (float)max_life),
              0.5 - 2*(life / (float)max_life),
              1 - life / (float)max_life);

    float r = 0.05f;

    // We use camera up and left vectors to billboard the triangles
    // so they're facing the camera all the time

    // Top right
    glTexCoord2f(xMax, yMin);
    glVertex3f(pos.m_x + r * (-_cl.m_x + _cu.m_x),
               pos.m_y + r * (-_cl.m_y + _cu.m_y),
               pos.m_z + r * (-_cl.m_z + _cu.m_z));

    // Top left
    glTexCoord2f(xMin, yMin);
    glVertex3f(pos.m_x - r * (-_cl.m_x - _cu.m_x),
               pos.m_y - r * (-_cl.m_y - _cu.m_y),
               pos.m_z - r * (-_cl.m_z - _cu.m_z));

    // Bot right
    glTexCoord2f(xMax, yMax);
    glVertex3f(pos.m_x + r * (-_cl.m_x - _cu.m_x),
               pos.m_y + r * (-_cl.m_y - _cu.m_y),
               pos.m_z + r * (-_cl.m_z - _cu.m_z));

    // Top left
    glTexCoord2f(xMin, yMin);
    glVertex3f(pos.m_x - r * (-_cl.m_x - _cu.m_x),
               pos.m_y - r * (-_cl.m_y - _cu.m_y),
               pos.m_z - r * (-_cl.m_z - _cu.m_z));

    // Bot left
    glTexCoord2f(xMin, yMax);
    glVertex3f(pos.m_x - r * (-_cl.m_x + _cu.m_x),
               pos.m_y - r * (-_cl.m_y + _cu.m_y),
               pos.m_z - r * (-_cl.m_z + _cu.m_z));

    // Bot right
    glTexCoord2f(xMax, yMax);
    glVertex3f(pos.m_x + r * (-_cl.m_x - _cu.m_x),
               pos.m_y + r * (-_cl.m_y - _cu.m_y),
               pos.m_z + r * (-_cl.m_z - _cu.m_z));
  }

  ++life;
}

