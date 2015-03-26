#include <OpenGL/gl.h>
#include <cmath>
#include <iostream>

#include "Projectile.h"
#include "Defs.h"

void Projectile::drawProjectile()
{
  // Calculate multipliers for the left and the up vectors
  // i.e. how much to move on each vector in each frame
  float lMul = PROJECTILESPEED * cosf(dir);
  float uMul = PROJECTILESPEED * sinf(dir);

  pos.m_x -= lMul * left.m_x;
  pos.m_y -= lMul * left.m_y;
  pos.m_z -= lMul * left.m_z;

  pos.m_x += uMul * up.m_x;
  pos.m_y += uMul * up.m_y;
  pos.m_z += uMul * up.m_z;

  // Check if the projectile has reached the atmosphere,
  // if so we'll calculte new up/left vectors for it to
  // bend around the atmosphere
  if(pos.length() > WORLDRADIUS*ASPHERERADIUS)
  {
    pos.normalize();
    left = pos.cross(up);
    left.normalize();
    pos *= WORLDRADIUS*ASPHERERADIUS;
  }
  else
  {
    // While the projectiles are under the atmosphere we
    // move them upwards more rapidly
    pos += Vec4(0, 0, 1)*PROJECTILESPEED;
  }


  normal.normalGL();
  glColor4f(1,
            1 * (life/(float)35.0),
            1 * (life/(float)70.0),
            life/(float)35.0);

  glNormal3f(0, 0, 1);
  pos.vertexGL();

  --life;
}

void Projectile::cube()
{
}
