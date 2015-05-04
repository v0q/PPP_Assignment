/*
 Copyright © 2015 Teemu Lindborg
 SDAGE 1st year 2nd PPP Assignment
*/

#include "Particles.h"

// ---------------------------------------------------------------------------------------
/// @file Particles.cpp
/// @brief Implementation of the particle draw and move functions
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------
void Particle::draw()
{
  // Calculate the color of a particle based on how long it has lived relative to its
  // maximum lifetime
  glColor4f(1,
            1 - (m_life / (float)m_max_life),
            0.5 - 2*(m_life / (float)m_max_life),
            1 - m_life / (float)m_max_life);
  m_pos.vertexGL();
}
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------
void Particle::move()
{
  m_pos.m_x += (m_pos.m_x > 0 ? -m_moveX : m_moveX);
  m_pos.m_y += (m_pos.m_y > 0 ? -m_moveY : m_moveY);
  m_pos.m_z += (m_pos.m_z > 0 ? -m_moveZ : m_moveZ);
}
// ---------------------------------------------------------------------------------------
