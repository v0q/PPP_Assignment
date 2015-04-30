#ifdef LINUX
  #include <GL/gl.h>
#endif
#ifdef DARWIN
  #include <OpenGL/gl.h>
#endif

#include <iostream>
#include <SDL2/SDL.h>

#include "Defs.h"
#include "World.h"
#include "Audio.h"
#include "Icosahedron.h"
#include "TextureOBJ.h"
#include "NCCA/Vec4.h"
#include "NCCA/GLFunctions.h"

World::World() : max_asteroids(10)
{
  rng.seed(time(NULL));
  loadModel("models/sphere.obj", m_skybox);
  loadModel("models/asteroid1.obj", m_asteroid[0]);
  loadModel("models/asteroid2.obj", m_asteroid[1]);
  audio::loadSound("sounds/explosion.wav", &a_explosion);
  audio::loadSound("sounds/bg_music.wav", &a_bgmusic);
  atmosphere();
  skybox();
  genALists();

  Mix_VolumeChunk(a_bgmusic, MIX_MAX_VOLUME * 0.8f);
  Mix_VolumeChunk(a_explosion, MIX_MAX_VOLUME * 0.4f);

  Mix_PlayChannel(-1, a_bgmusic, -1);
}

World::~World()
{
  stars.clear();
  std::vector<Vec4>().swap(stars);
  w_displayList.clear();
  std::vector<GLuint>().swap(w_displayList);
  asteroids.clear();
  std::vector<Asteroid>().swap(asteroids);
  a_ColIndices.clear();
  std::list<int>().swap(a_ColIndices);

  //Clear skybox model related stuff
  freeModelMem(m_skybox);

  for(int i = 0; i < 2; ++i)
    freeModelMem(m_asteroid[i]);

  Mix_FreeChunk(a_explosion);
  Mix_FreeChunk(a_bgmusic);
}

void World::drawWorld()
{
  generate_Asteroids();
  partByDist();

  glCallLists(w_displayList.size(), GL_UNSIGNED_INT, &w_displayList[0]);
  drawPlanet();
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

void World::drawPlanet()
{
  glScalef(WORLDRADIUS, WORLDRADIUS, WORLDRADIUS);
  m_planet.draw();
}

void World::atmosphere()
{
  GLuint id = glGenLists(1);
  glNewList(id, GL_COMPILE);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glColor4f(0.114, 0.431, 0.506, 0.3);
    glScalef(WORLDRADIUS*ASPHERERADIUS, WORLDRADIUS*ASPHERERADIUS, WORLDRADIUS*ASPHERERADIUS);

    glBegin(GL_TRIANGLES);

        tSphere(4, 1);

    glEnd();

    glScalef(1.0f/(WORLDRADIUS*ASPHERERADIUS), 1.0f/(WORLDRADIUS*ASPHERERADIUS), 1.0f/(WORLDRADIUS*ASPHERERADIUS));

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  glEndList();
  w_displayList.push_back(id);
}

void World::skybox()
{
  loadTexture("textures/sb_cube.png", skyBoxTexId);

  GLuint id = glGenLists(1);
  glNewList(id, GL_COMPILE);

    glDepthMask(GL_FALSE);
    // Scale the skybox to the set radius
    glScalef(WORLDRADIUS*ASPHERERADIUS*SKYBOXRADIUS, WORLDRADIUS*ASPHERERADIUS*SKYBOXRADIUS, WORLDRADIUS*ASPHERERADIUS*SKYBOXRADIUS);

    // We need to bind the texture inside the list so that the texture is rendered
    // whenever the list is called.
    glBindTexture(GL_TEXTURE_2D, skyBoxTexId);
    glBegin(GL_TRIANGLES);

      // Set the skybox to be "fully colored" and draw get the triangles of the loaded mesh
      glColor4f(1, 1, 1, 1);
      for(int i = 0; i < (int)m_skybox.Ind.size(); i += 3)
      {
        m_skybox.Norms[m_skybox.Ind[i + 2] - 1].normalInvGL();
        m_skybox.Text[m_skybox.Ind[i + 1] - 1].textureGL();
        m_skybox.Verts[m_skybox.Ind[i] - 1].vertexGL();
      }

    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);

    glScalef(1.0f/(WORLDRADIUS*ASPHERERADIUS*SKYBOXRADIUS), 1.0f/(WORLDRADIUS*ASPHERERADIUS*SKYBOXRADIUS), 1.0f/(WORLDRADIUS*ASPHERERADIUS*SKYBOXRADIUS));

    glDepthMask(GL_TRUE);
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

  normal.normalGL();

  u = asin(_a.m_x)/PI + 0.5;
  v = asin(_a.m_y)/PI + 0.5;

  glTexCoord2f(u, v);
  _a.vertexGL();

  u = ((atan2(_b.m_x, _b.m_z) / PI) + 1.0f) * 0.5f;
  v = (asin(_b.m_y) / PI) + 0.5f;

  glTexCoord2f(u, v);
  _b.vertexGL();

  u = asin(_c.m_x)/PI + 0.5;
  v = asin(_c.m_y)/PI + 0.5;

  glTexCoord2f(u, v);
  _c.vertexGL();
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

void World::generate_Asteroids()
{
  boost::random::uniform_int_distribution<> u_random(1, 100);

  if(u_random(rng)/100.0 > 0.95 && (int)asteroids.size() < max_asteroids)
  {
    Vec4 aPos(u_random(rng)/100.0 * 2.0 - 1.0 + 0.01f, u_random(rng)/100.0 * 2.0 - 1.0 + 0.01f, u_random(rng)/100.0 * 2.0 - 1.0 + 0.01f);
    aPos.normalize();

    Vec4 aDir = aPos * - 1;
    Vec4 aSide(u_random(rng)/100.0,
              u_random(rng)/100.0,
              0);

    if(fabs(aPos.m_z) > 0.001)
      aSide.m_z = -(aSide.m_x*aPos.m_x + aSide.m_y*aPos.m_y) / aPos.m_z;

    Vec4 aUp;
    aUp = aSide.cross(aPos);

    aPos *= SKYBOXRADIUS;

    float size = u_random(rng)/100.0 * 0.8f + 0.1f;
    int type = u_random(rng)%2;

    asteroids.push_back(Asteroid(aPos, aDir,
                                 aUp, aSide,
                                 size, fmod(u_random(rng)/100.0, 0.04f) + 0.0315f,
                                 size * 150, type));
  }

  glBindTexture(GL_TEXTURE_2D, aTexId);
  for(int i = 0; i < (int)asteroids.size(); ++i)
  {
    if(asteroids[i].life > 0)
      asteroids[i].draw(a_displayList);
    else
    {
      if(asteroids[i].size > 0.5f)
      {
        for(int j = 0; j < 2; ++j)
        {
          Vec4 aPos = asteroids[i].pos;
          aPos.normalize();
          Vec4 new_dir = aPos * - 1;
          Vec4 new_side(u_random(rng)/100.0 + 0.01f,
                    u_random(rng)/100.0 + 0.01f,
                    0);
          Vec4 new_up = new_side.cross(aPos);

          if(fabs(aPos.m_z) > 0.001)
            new_side.m_z = -(new_side.m_x*aPos.m_x + new_side.m_y*aPos.m_y) / aPos.m_z;

          float new_size = asteroids[i].size*fmod(u_random(rng)/100.0, 0.35f) + 0.25f;

          asteroids.push_back(Asteroid(asteroids[i].pos, new_dir,
                                       new_up, new_side,
                                       new_size, fmod(u_random(rng)/100.0, 0.055) + 0.02f,
                                       new_size*150, u_random(rng)%2));
        }
      }

      Mix_PlayChannel(-1, a_explosion, 0);

      asteroids.erase(asteroids.begin() + i);
    }
  }
  glBindTexture(GL_TEXTURE_2D, 0);

}

void World::partByDist()
{
  for(int i = 0; i < (int)asteroids.size(); ++i)
    if(fabs(asteroids[i].pos.length() - WORLDRADIUS*ASPHERERADIUS) < 0.05)
      a_ColIndices.push_back(i);
  a_ColIndices.sort();
  a_ColIndices.unique();
}

void World::genALists()
{
  loadTexture("textures/Am2.jpg", aTexId);

  GLuint id = glGenLists(1);
  glNewList(id, GL_COMPILE);
    glBegin(GL_TRIANGLES);
      for(int i = 0; i < (int)m_asteroid[0].Ind.size(); i += 9)
      {
        m_asteroid[0].Norms[m_asteroid[0].Ind[i + 2] - 1].normalGL();
        m_asteroid[0].Text[m_asteroid[0].Ind[i + 1] - 1].textureGL();
        m_asteroid[0].Verts[m_asteroid[0].Ind[i] - 1].vertexGL();

        m_asteroid[0].Text[m_asteroid[0].Ind[i + 4] - 1].textureGL();
        m_asteroid[0].Verts[m_asteroid[0].Ind[i + 3] - 1].vertexGL();

        m_asteroid[0].Text[m_asteroid[0].Ind[i + 7] - 1].textureGL();
        m_asteroid[0].Verts[m_asteroid[0].Ind[i + 6] - 1].vertexGL();
      }
    glEnd();
  glEndList();

  a_displayList.push_back(id);

  id = glGenLists(1);
  glNewList(id, GL_COMPILE);
    glBegin(GL_TRIANGLES);
    for(int i = 0; i < (int)m_asteroid[1].Ind.size(); i += 9)
    {
      m_asteroid[1].Norms[m_asteroid[1].Ind[i + 2] - 1].normalGL();
      m_asteroid[1].Text[m_asteroid[1].Ind[i + 1] - 1].textureGL();
      m_asteroid[1].Verts[m_asteroid[1].Ind[i] - 1].vertexGL();

      m_asteroid[1].Text[m_asteroid[1].Ind[i + 4] - 1].textureGL();
      m_asteroid[1].Verts[m_asteroid[1].Ind[i + 3] - 1].vertexGL();

      m_asteroid[1].Text[m_asteroid[1].Ind[i + 7] - 1].textureGL();
      m_asteroid[1].Verts[m_asteroid[1].Ind[i + 6] - 1].vertexGL();
    }
    glEnd();
  glEndList();

  a_displayList.push_back(id);
}
