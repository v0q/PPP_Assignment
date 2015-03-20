#include <iostream>
#include <OpenGL/gl.h>
#include <SDL.h>

#include "Defs.h"
#include "World.h"
#include "Icosahedron.h"
#include "TextureOBJ.h"
#include "NCCA/Vec4.h"
#include "NCCA/GLFunctions.h"

void World::drawWorld()
{
  generate_Asteroids();
  partByDist();
  glCallLists(w_displayList.size(), GL_UNSIGNED_INT, &w_displayList[0]);
}

void World::planet()
{
  GLuint id = glGenLists(1);
  glNewList(id, GL_COMPILE);
    glScalef(WORLDRADIUS, WORLDRADIUS, WORLDRADIUS);
      glColor3f(1.0, 1.0, 1.0);
      tSphere(3, 1);

  glEndList();
  w_displayList.push_back(id);
}

void World::atmosphere()
{
  GLuint id = glGenLists(1);
  glNewList(id, GL_COMPILE);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColor4f(0.114, 0.431, 0.506, 0.3);

      glScalef(ASPHERERADIUS, ASPHERERADIUS, ASPHERERADIUS);
        tSphere(4, 1);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  glEndList();
  w_displayList.push_back(id);
}

void World::skybox()
{
  GLuint id = glGenLists(1);
  glNewList(id, GL_COMPILE);

    glScalef(SKYBOXRADIUS, SKYBOXRADIUS, SKYBOXRADIUS);

      loadTexture("textures/skybox2.png");

      glColor3f(0.4, 0.4, 0.4);
      tSphere(3, -1);

      glBindTexture(GL_TEXTURE_2D, 0);
  glEndList();
  w_displayList.push_back(id);
}

void World::subd(Vec4 &_a, Vec4 &_b, Vec4 &_c, int _d, int _ndir) const
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

    subd(_a, v[0], v[1], _d - 1, _ndir);
    subd(v[0], _b, v[2], _d - 1, _ndir);
    subd(v[1], v[2], _c, _d - 1, _ndir);
    subd(v[0], v[1], v[2], _d - 1, _ndir);

    if(_d == 1)
    {
      drawTriangle(_a, v[0], v[1], _ndir);
      drawTriangle(v[0], _b, v[2], _ndir);
      drawTriangle(v[1], v[2], _c, _ndir);
      drawTriangle(v[0], v[1], v[2], _ndir);
    }
  }
}

void World::drawTriangle(Vec4 &_a, Vec4 &_b, Vec4 &_c, int _ndir) const
{
  Vec4 normal;
  float u, v;
  normal = (_a + _b + _c) * _ndir;
  normal.normalize();

  glBegin(GL_TRIANGLES);
    normal.normalGL();

    u = ((atan2(_a.m_x, _a.m_z) / PI) + 1.0f) * 0.5f;
    v = (asin(_a.m_y) / PI) + 0.5f;

    glTexCoord2f(u, v);
    _a.vertexGL();

    u = ((atan2(_b.m_x, _b.m_z) / PI) + 1.0f) * 0.5f;
    v = (asin(_b.m_y) / PI) + 0.5f;

    glTexCoord2f(u, v);
    _b.vertexGL();

    u = ((atan2(_c.m_x, _c.m_z) / PI) + 1.0f) * 0.5f;
    v = (asin(_c.m_y) / PI) + 0.5f;

    glTexCoord2f(u, v);
    _c.vertexGL();
  glEnd();
}

void World::tSphere(int _d, int _ndir) const
{
  for(int k = 0; k < 20; ++k)
  {
    icosHedron[k][0].normalize();
    icosHedron[k][1].normalize();
    icosHedron[k][2].normalize();
    subd(icosHedron[k][0], icosHedron[k][1], icosHedron[k][2], _d, _ndir);
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
    s *= fmod(std::rand(),SKYBOXRADIUS-WORLDRADIUS*ASPHERERADIUS) + 3*WORLDRADIUS*ASPHERERADIUS;
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

void World::generate_Asteroids()
{
  if(std::rand()/(float)RAND_MAX > 0.95 && (int)asteroids.size() < max_asteroids)
  {
    Vec4 aPos(std::rand()/(float)RAND_MAX * 2 - 1, std::rand()/(float)RAND_MAX  * 2 - 1, std::rand()/(float)RAND_MAX  * 2 - 1);
    aPos.normalize();

    Vec4 aDir = aPos * - 1;

    aPos *= SKYBOXRADIUS;
    float size = fmod(std::rand(), 5.0) + 1.0f;
    asteroids.push_back(Asteroid(aPos, aDir,
                                 size, fmod(std::rand(), 0.035) + 0.015f,
                                 size*100/6.0));
  }

  for(int i = 0; i < (int)asteroids.size(); ++i)
  {
    if(asteroids[i].life > 0)
      asteroids[i].draw();
    else
      asteroids.erase(asteroids.begin() + i);
  }
}

void World::partByDist()
{
  for(int i = 0; i < (int)asteroids.size(); ++i)
    if(fabs(asteroids[i].pos.length() - WORLDRADIUS*ASPHERERADIUS) < 0.05)
      a_ColIndices.push_back(i);
  a_ColIndices.sort();
  a_ColIndices.unique();
}
