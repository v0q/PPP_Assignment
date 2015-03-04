#include <OpenGL/gl.h>
#include <iostream>

#include "World.h"
#include "Icosahedron.h"
#include <SDL.h>
#include "NCCA/Vec4.h"
#include "NCCA/GLFunctions.h"

World::World()
{

}

World::~World()
{

}

void World::drawWorld(Universe _u) const
{
  // TODO(Teemu): Universe/world rotation

  glPushMatrix();
    //glLoadIdentity();
    //glTranslatef(0, 0, -4);
    //glMultMatrixf(Transform.m_openGL);

    glRotatef(_u.rot, _u.r.m_x, _u.r.m_y, _u.r.m_z);

    glScalef(WORLDRADIUS, WORLDRADIUS, WORLDRADIUS);
      planet();

    //glScalef(1.225f, 1.225f, 1.225f);
    //  atmosphere();
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
  glColor3f(1.0, 1.0, 1.0);
  tSphere(5);
}

void World::atmosphere() const
{

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glColor4f(0.114, 0.431, 0.506, 0.3);

    //sphere(WORLDRADIUS*1.25f);
    tSphere(4);

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glDisable(GL_BLEND);


}

void World::subd(Vec4 &_a, Vec4 &_b, Vec4 &_c, int _d) const
{
  Vec4 v[3];

  if(_d > 0)
  {
    v[0] = (_a + _b)/2.0;
    v[1] = (_a + _c)/2.0;
    v[2] = (_b + _c)/2.0;


    v[0].normalize();
    v[1].normalize();
    v[2].normalize();

    subd(_a, v[0], v[1], _d - 1);
    subd(v[0], _b, v[2], _d - 1);
    subd(v[1], v[2], _c, _d - 1);
    subd(v[0], v[1], v[2], _d - 1);

    if(_d == 1)
    {
      drawTriangle(_a, v[0], v[1]);
      drawTriangle(v[0], _b, v[2]);
      drawTriangle(v[1], v[2], _c);
      drawTriangle(v[0], v[1], v[2]);
    }
  }
}

void World::drawTriangle(Vec4 &_a, Vec4 &_b, Vec4 &_c) const
{
  glBegin(GL_TRIANGLES);
    _a.normalGL();
    _b.normalGL();
    _c.normalGL();

    _a.vertexGL();
    _b.vertexGL();
    _c.vertexGL();
  glEnd();
}

void World::tSphere(int _i) const
{
  for(int k = 0; k < 20; ++k)
  {
    icosHedron[k][0].normalize();
    icosHedron[k][1].normalize();
    icosHedron[k][2].normalize();
    subd(icosHedron[k][0], icosHedron[k][1], icosHedron[k][2], _i);
  }
}

void World::sphere(float _radius) const
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
     vertex = normal * _radius;
     normal.normalGL();
     vertex.vertexGL();
     // vert / normal 2
     normal.set(cosf(theta1) * cosf(theta3),sinf(theta1),cosf(theta1) * sinf(theta3));
     vertex = normal * _radius;
     normal.normalGL();
     vertex.vertexGL();
    } // end inner loop
  }// end outer loop
  glEnd();
}
