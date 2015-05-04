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

#include <cmath>
#include <iostream>

#include "Projectile.h"
#include "Defs.h"

// ---------------------------------------------------------------------------------------
/// @file Projectile.cpp
/// @brief Implementation of the projectile class functions
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------
void Projectile::drawProjectile(
                                const int _itAmt,
                                const Vec4 &_cu,
                                const Vec4 &_cl)
{
  // Calculating which sprite from the sprite sheet to use
  // based on the elapsed life of the projectile in relation
  // to it's maximum lifetime. This because the projectiles
  // can have different max lifetime and we want each one to
  // display the whole animation
  float tDim = 1.0/5.0;
  int step = floor(m_life*25/m_maxLife);

  // Getting the texture coordinates for each sprite
  float xMin = tDim * (step%5);
  float xMax = tDim * (step%5 + 1);
  float yMin = tDim * (step/5);
  float yMax = tDim * (step/5 + 1);

  // Iterate the movement to smooth it with higher movement speeds
  for(int i = 0; i < _itAmt; ++i)
  {
    // Calculate multipliers for the left and the up vectors
    // i.e. how much to move on each vector in each frame
    float lMul = (PROJECTILESPEED * cosf(m_dir)) / _itAmt;
    float uMul = (PROJECTILESPEED * sinf(m_dir)) / _itAmt;

    // Move the projectile
    m_pos.m_x -= lMul * m_left.m_x;
    m_pos.m_y -= lMul * m_left.m_y;
    m_pos.m_z -= lMul * m_left.m_z;

    m_pos.m_x += uMul * m_up.m_x;
    m_pos.m_y += uMul * m_up.m_y;
    m_pos.m_z += uMul * m_up.m_z;

    if(m_pos.length() < WORLDRADIUS*ASPHERERADIUS)
    {
      // While the projectiles are under the atmosphere we
      // move them upwards more rapidly. This is done by
      // moving the projectiles to their normal direction
      m_pos += Vec4(m_normal.m_x, m_normal.m_y, m_normal.m_z)*PROJECTILESPEED / _itAmt;
    }

    // Check if the projectile has reached the atmosphere,
    // if so we'll calculte new up/left vectors for it to
    // bend around the atmosphere
    if(m_pos.length() > WORLDRADIUS*ASPHERERADIUS)
    {
      m_pos.normalize();
      m_left = m_pos.cross(m_up);
      m_up = m_left.cross(m_pos);
      m_left.normalize();
      m_up.normalize();
      m_pos *= WORLDRADIUS*ASPHERERADIUS;
    }

    m_normal.normalGL();

    // Change the color of the projectile based on the elapsed life
    glColor4f(1,
              1 - (m_life / (float)m_maxLife),
              0.5 - 2*(m_life / (float)m_maxLife),
              1 - m_life / (float)m_maxLife);

    // Length of the triangle quad side
    float r = 0.05f;

    // We use camera up and left vectors to billboard the triangles
    // so they're facing the camera all the time

    // Top right
    glTexCoord2f(xMax, yMin);
    glVertex3f(m_pos.m_x + r * (-_cl.m_x + _cu.m_x),
               m_pos.m_y + r * (-_cl.m_y + _cu.m_y),
               m_pos.m_z + r * (-_cl.m_z + _cu.m_z));

    // Top left
    glTexCoord2f(xMin, yMin);
    glVertex3f(m_pos.m_x - r * (-_cl.m_x - _cu.m_x),
               m_pos.m_y - r * (-_cl.m_y - _cu.m_y),
               m_pos.m_z - r * (-_cl.m_z - _cu.m_z));

    // Bot right
    glTexCoord2f(xMax, yMax);
    glVertex3f(m_pos.m_x + r * (-_cl.m_x - _cu.m_x),
               m_pos.m_y + r * (-_cl.m_y - _cu.m_y),
               m_pos.m_z + r * (-_cl.m_z - _cu.m_z));

    // Top left
    glTexCoord2f(xMin, yMin);
    glVertex3f(m_pos.m_x - r * (-_cl.m_x - _cu.m_x),
               m_pos.m_y - r * (-_cl.m_y - _cu.m_y),
               m_pos.m_z - r * (-_cl.m_z - _cu.m_z));

    // Bot left
    glTexCoord2f(xMin, yMax);
    glVertex3f(m_pos.m_x - r * (-_cl.m_x + _cu.m_x),
               m_pos.m_y - r * (-_cl.m_y + _cu.m_y),
               m_pos.m_z - r * (-_cl.m_z + _cu.m_z));

    // Bot right
    glTexCoord2f(xMax, yMax);
    glVertex3f(m_pos.m_x + r * (-_cl.m_x - _cu.m_x),
               m_pos.m_y + r * (-_cl.m_y - _cu.m_y),
               m_pos.m_z + r * (-_cl.m_z - _cu.m_z));
  }

  // Increase the elapsed life
  ++m_life;
}
// ---------------------------------------------------------------------------------------

