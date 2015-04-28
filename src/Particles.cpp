#include "Particles.h"

void Particle::draw() const
{
  glColor4f(1,
            1 - (life / (float)max_life),
            0.5 - 2*(life / (float)max_life),
            1 - life / (float)max_life);
  glVertex3f(pos.m_x, pos.m_y, pos.m_z);
}

void Particle::move()
{
  pos.m_x += (pos.m_x > 0 ? -moveX : moveX);
  pos.m_y += (pos.m_y > 0 ? -moveY : moveY);
  pos.m_z += (pos.m_z > 0 ? -moveZ : moveZ);
}
