/*
 Copyright © 2015 Teemu Lindborg
 SDAGE 1st year 2nd PPP Assignment
*/

#include <iostream>

#include "Asteroids.h"

// ---------------------------------------------------------------------------------------
/// @file Asteroids.cpp
/// @brief Implementation of the asteroid drawing and moving
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------
void Asteroid::draw(
                    const std::vector<GLuint> &_dL
                   )
{
  // Call the move function
  move();
  glPushMatrix();

    // Rotate the asteroid, scale it and translate it to its correct position
    glTranslatef(m_pos.m_x, m_pos.m_y, m_pos.m_z);
    glScalef(m_size, m_size, m_size);
    glRotatef(m_rot, 1.0f, 1.0f, 1.0f);

    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    // Call the displaylist with the wanted asteroid model
    glCallList(_dL[c_aType]);

  glPopMatrix();
}
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------
void Asteroid::move()
{
  // Check if asteroid is yet to reach the atmosphere
  // and move it towards the planet if so
  if(m_pos.length() > WORLDRADIUS*ASPHERERADIUS && m_speed > 0.031f)
  {
    m_pos += m_dir * m_speed;
    m_rot += 5;
  }
  else
  {
    // If the asteroid has reached the atmosphere we reduce the speed and
    // calculate new up and side vectors to move the asteroid around the
    // planet but keeping it on the atmosphere surface
    m_speed = 0.03f;

    m_pos.normalize();
    m_side = m_pos.cross(m_up);
    m_side.normalize();
    m_pos *= WORLDRADIUS*ASPHERERADIUS;

    m_pos.m_x += m_speed * m_side.m_x;
    m_pos.m_y += m_speed * m_side.m_y;
    m_pos.m_z += m_speed * m_side.m_z;

    ++m_rot;
  }
}
// ---------------------------------------------------------------------------------------
