#include <iostream>
#include <OpenGL/gl.h>
#include <SDL.h>

#include "World.h"
#include "Defs.h"
#include "Icosahedron.h"
#include "NCCA/Vec4.h"
#include "NCCA/GLFunctions.h"

void World::drawWorld() const
{
  planet();
  atmosphere();
  skybox();
}

void World::planet() const
{
  glColor3f(1.0, 1.0, 1.0);
  glScalef(WORLDRADIUS, WORLDRADIUS, WORLDRADIUS);
  tSphere(3, 1);
}

void World::atmosphere() const
{
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glColor4f(0.114, 0.431, 0.506, 0.3);

    glScalef(ASPHERERADIUS, ASPHERERADIUS, ASPHERERADIUS);
    tSphere(4, 1);

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void World::skybox() const
{
  glScalef(SKYBOXRADIUS, SKYBOXRADIUS, SKYBOXRADIUS);
    glColor3f(0.4, 0.4, 0.4);
    tSphere(3, -1);
}

void World::subd(Vec4 &_a, Vec4 &_b, Vec4 &_c, int _d, int _dir) const
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

    subd(_a, v[0], v[1], _d - 1, _dir);
    subd(v[0], _b, v[2], _d - 1, _dir);
    subd(v[1], v[2], _c, _d - 1, _dir);
    subd(v[0], v[1], v[2], _d - 1, _dir);

    if(_d == 1)
    {
      drawTriangle(_a, v[0], v[1], _dir);
      drawTriangle(v[0], _b, v[2], _dir);
      drawTriangle(v[1], v[2], _c, _dir);
      drawTriangle(v[0], v[1], v[2], _dir);
    }
  }
}

void World::drawTriangle(Vec4 &_a, Vec4 &_b, Vec4 &_c, int _dir) const
{
  Vec4 normal;
  normal = (_a + _b + _c) * _dir;
  normal.normalize();

  glBegin(GL_TRIANGLES);
    normal.normalGL();

    _a.vertexGL();
    _b.vertexGL();
    _c.vertexGL();
  glEnd();
}

void World::tSphere(int _d, int _dir) const
{
  for(int k = 0; k < 20; ++k)
  {
    icosHedron[k][0].normalize();
    icosHedron[k][1].normalize();
    icosHedron[k][2].normalize();
    subd(icosHedron[k][0], icosHedron[k][1], icosHedron[k][2], _d, _dir);
  }
}

void World::initStars(int _a)
{
  for(int i = 0; i < _a; ++i)
  {
    Vec4 s(std::rand()/(float)RAND_MAX * 2 - 1,
           std::rand()/(float)RAND_MAX * 2 - 1,
           std::rand()/(float)RAND_MAX * 2 - 1);

    s.normalize();
    s *= fmod(std::rand(),SKYBOXRADIUS-WORLDRADIUS*ASPHERERADIUS) + WORLDRADIUS*ASPHERERADIUS*ASPHERERADIUS;
    s.m_w = 1 - (s.length()/SKYBOXRADIUS);
    stars.push_back(s);
  }
}

void World::drawStars(Vec4 _c) const
{
  glPointSize(6);
  glBegin(GL_POINTS);
      for(int i = 0; i < (int)stars.size(); ++i)
      {
        glColor4f(1, 1, 1, (stars[i].m_w > 0.4 ? stars[i].m_w - 0.4f : stars[i].m_w));
        glNormal3f(_c.m_x, _c.m_y, _c.m_z);
        glVertex3f(stars[i].m_x, stars[i].m_y, stars[i].m_z);
      }
  glEnd();
}
