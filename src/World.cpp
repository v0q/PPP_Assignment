#include <OpenGL/gl.h>

#include "World.h"
#include "NCCA/Vec4.h"
#include "NCCA/GLFunctions.h"

World::World()
{

}

World::~World()
{

}

void World::drawWorld() const
{
  glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    planet();
  glPopMatrix();
}

void World::updateCamera()
{
  GLFunctions::lookAt(Vec4(cam.ex, cam.ex, cam.ez),
                      Vec4(cam.lx, cam.ly, cam.lz),
                      Vec4(cam.ux, cam.uy, cam.uz));

  GLFunctions::perspective(cam.fov, cam.a, cam.n, cam.f);
}

void World::planet() const
{
  //  Sphere code based on a function Written by Paul Bourke.
  //  http://astronomy.swin.edu.au/~pbourke/opengl/sphere/
  // the next part of the code calculates the P,N,UV of the sphere for tri_strips

  float theta1 = 0.0;
  float theta2 = 0.0;
  float theta3 = 0.0;
  Vec4 normal;
  Vec4 vertex;

  glBegin(GL_TRIANGLE_STRIP);

  // now fill in a vertData structure and add to the data list for our sphere
  for( int i = 0; i < PRECISION/2; ++i )
  {
   theta1 = i * TWO_PI / PRECISION - PI2;
   theta2 = (i + 1) * TWO_PI / PRECISION - PI2;

   for( int j = 0; j <= PRECISION; ++j )
   {
     theta3 = j * TWO_PI / PRECISION;
     normal.set(cosf(theta2) * cosf(theta3),sinf(theta2),cosf(theta2) * sinf(theta3));
     vertex=normal * WORLDRADIUS;
     normal.normalGL();
     vertex.vertexGL();
     // vert / normal 2
     normal.set(cosf(theta1) * cosf(theta3),sinf(theta1),cosf(theta1) * sinf(theta3));
     vertex=normal * WORLDRADIUS;
     normal.normalGL();
     vertex.vertexGL();
    } // end inner loop
  }// end outer loop
  glEnd();
  // end citation
}
