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

#include <iostream>
#include <SDL2/SDL.h>

#include "Defs.h"
#include "World.h"
#include "Audio.h"
#include "Icosahedron.h"
#include "TextureOBJ.h"
#include "NCCA/Vec4.h"
#include "NCCA/GLFunctions.h"

// ---------------------------------------------------------------------------------------
/// @file World.cpp
/// @brief Implementation of the world class functions
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------
World::World() :
  m_maxAsteroids(10)
{
  // Set the seed of the boost rng to whatever time it is when to program is run
  // to get different values each time the program is run.
  m_rng.seed(time(NULL));

  // Loads in the skybox and asteroid models and stores the data to their
  // respective model structures
  loadModel("models/sphere.obj", m_skybox);
  loadModel("models/asteroid1.obj", m_asteroid[0]);
  loadModel("models/asteroid2.obj", m_asteroid[1]);

// HACKY SOLUTION START
#ifdef LINUX
  loadTexture("textures/sb_90.png", m_skyBoxTexId);
#endif
#ifdef DARWIN
  loadTexture("textures/sb_cube.png", m_skyBoxTexId);
#endif
// HACKY SOLUTION END

  // Loads in the asteroid texture
  loadTexture("textures/Am2.jpg", m_aTexId);

  // Loads the asteroid explosion suond and background music
  audio::loadSound("sounds/explosion.wav", &m_aExplosion);
  audio::loadSound("sounds/bg_music.wav", &m_bgMusic);

  // Call the functions that generate the displaylists for skybox,
  // atmosphere geodesic sphere and asteroids
  skybox();
  atmosphere();
  genALists();

  // Set the volume levels for the explosions and background music
  Mix_VolumeChunk(m_bgMusic, MIX_MAX_VOLUME * 0.8f);
  Mix_VolumeChunk(m_aExplosion, MIX_MAX_VOLUME * 0.4f);

  // Start playing background music and loop it forever
  Mix_PlayChannel(-1, m_bgMusic, -1);
}
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------
World::~World()
{
  // Clean up the displaylists, asteroid and star data
  m_stars.clear();
  std::vector<Vec4>().swap(m_stars);
  m_wDisplayList.clear();
  std::vector<GLuint>().swap(m_wDisplayList);
  m_asteroids.clear();
  std::vector<Asteroid>().swap(m_asteroids);
  m_aColIndices.clear();
  std::list<int>().swap(m_aColIndices);

  // Clean up the memory allocated for the skybox and asteroid models
  freeModelMem(m_skybox);

  for(int i = 0; i < 2; ++i)
    freeModelMem(m_asteroid[i]);

  // Frees the memory allocated for the audio
  Mix_FreeChunk(m_aExplosion);
  Mix_FreeChunk(m_bgMusic);
}
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------
void World::drawWorld()
{
  // Draws the stars, generate and draw the asteroids and do the spatial partitioning
  drawStars();
  generate_Asteroids();
  partByDist();

  // Calls the displaylists that draw the atmosphere and skybox and finally the planet
  glCallLists(m_wDisplayList.size(), GL_UNSIGNED_INT, &m_wDisplayList[0]);
  drawPlanet();
}
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------
void World::drawStars() const
{
  glPointSize(6);
  glBegin(GL_POINTS);
      for(int i = 0; i < (int)m_stars.size(); ++i)
      {
        glColor4f(1.0f, 1.0f, 1.0f, m_stars[i].m_w);
        glNormal3f(0.0f, 0.0f, 1.0f);
        m_stars[i].vertexGL();
      }
  glEnd();
}
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------
void World::drawPlanet()
{
  // Scale the planet by the defined world radius and call the draw function of the
  // planet object
  glScalef(WORLDRADIUS, WORLDRADIUS, WORLDRADIUS);
  m_planet.draw();
}
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------
void World::atmosphere()
{
  // Generate the displaylist for the atmosphere
  GLuint id = glGenLists(1);
  glNewList(id, GL_COMPILE);

    // Turn the polygon mode to GL_LINE so the atmosphere will
    // be displayed in wireframe mode
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Set the color to a blueish value and set the opacity to 60%
    glColor4f(0.114, 0.431, 0.506, 0.6);

    // Scale the atmosphere
    glScalef(WORLDRADIUS*ASPHERERADIUS, WORLDRADIUS*ASPHERERADIUS, WORLDRADIUS*ASPHERERADIUS);

    glBegin(GL_TRIANGLES);

        // Calling the triangle sphere/geodesic sphere function with the subdivison
        // level 4 to generate the actual atmosphere
        tSphere(4);

    glEnd();

    // Return the scale back to normal as we're not loading identity with every element
    glScalef(1.0f/(WORLDRADIUS*ASPHERERADIUS), 1.0f/(WORLDRADIUS*ASPHERERADIUS), 1.0f/(WORLDRADIUS*ASPHERERADIUS));

    // Turn the polygon mode back to fill so no other objects will be affected by
    // the wireframe mode
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  glEndList();
  m_wDisplayList.push_back(id);
}
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------
void World::skybox()
{
  // Generate a displaylist for the skybox
  GLuint id = glGenLists(1);
  glNewList(id, GL_COMPILE);

    // We disable lighting and depth mask/testing as the skybox should be fully lit due to
    // it being a space scenery where the elements kinda "bring light to the scene"
    glDisable(GL_LIGHTING);
    glDepthMask(GL_FALSE);
    // Scale the skybox
    glScalef(WORLDRADIUS*ASPHERERADIUS*SKYBOXRADIUS, WORLDRADIUS*ASPHERERADIUS*SKYBOXRADIUS, WORLDRADIUS*ASPHERERADIUS*SKYBOXRADIUS);

    // Binding the texture inside the list so that the texture is rendered
    // whenever the list is called.
    glBindTexture(GL_TEXTURE_2D, m_skyBoxTexId);
    glBegin(GL_TRIANGLES);

      glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
      for(int i = 0; i < (int)m_skybox.m_Ind.size(); i += 3)
      {
        m_skybox.m_Norms[m_skybox.m_Ind[i + 2] - 1].normalInvGL();
        m_skybox.m_Text[m_skybox.m_Ind[i + 1] - 1].textureGL();
        m_skybox.m_Verts[m_skybox.m_Ind[i] - 1].vertexGL();
      }

    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);

    // Return the scale back to normal as we're not loading identity with every element
    glScalef(1.0f/(WORLDRADIUS*ASPHERERADIUS*SKYBOXRADIUS), 1.0f/(WORLDRADIUS*ASPHERERADIUS*SKYBOXRADIUS), 1.0f/(WORLDRADIUS*ASPHERERADIUS*SKYBOXRADIUS));

    // Turning depth mask/testing and lighting back on
    glDepthMask(GL_TRUE);
    glEnable(GL_LIGHTING);
  glEndList();
  m_wDisplayList.push_back(id);
}
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------
void World::subd(const Vec4 &_a, const Vec4 &_b, const Vec4 &_c, const int _d) const
{
  // A vector array holding the new points achieved by the subdivision
  Vec4 v[3];

  // As this is a recursive function, we'll check that we're still subdividing.
  // If not the function will reach its end and "return"
  if(_d > 0)
  {

    // Calculate the subdivided points by getting the mid point of each side
    // of the triangle
    v[0] = (_a + _b)/2.0;
    v[1] = (_a + _c)/2.0;
    v[2] = (_b + _c)/2.0;

    // Normalise the new points as they will be used for the next subdivision
    v[0].normalize();
    v[1].normalize();
    v[2].normalize();

    // Call the subdivide function with the new triangles formed by the
    // current subdivision:
    /*   /\      /\
        /  \ => /__\
       /____\  /_\/_\ */

    subd(_a, v[0], v[1], _d - 1);
    subd(v[0], _b, v[2], _d - 1);
    subd(v[1], v[2], _c, _d - 1);
    subd(v[0], v[1], v[2], _d - 1);

    // If we've reached the last subdivision level we'll render out the triangles
    // As we only want the to draw the same sized triangles
    if(_d == 1)
    {
      drawTriangle(_a, v[0], v[1]);
      drawTriangle(v[0], _b, v[2]);
      drawTriangle(v[1], v[2], _c);
      drawTriangle(v[0], v[1], v[2]);
    }
  }
}
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------
void World::drawTriangle(
                         const Vec4 &_a,
                         const Vec4 &_b,
                         const Vec4 &_c
                        ) const
{
  // Calculating the normal of a face (not necessarily needed here as we're
  // only using this method for the wireframed atmosphere.
  Vec4 normal;
  normal = _a + _b + _c;
  normal.normalize();

  normal.normalGL();

  _a.vertexGL();
  _b.vertexGL();
  _c.vertexGL();
}
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------
void World::tSphere(
                    const int _d
                   ) const
{
  // Loop through the icosahedron shape and subdivide each triangle
  for(int k = 0; k < 20; ++k)
  {
    icosHedron[k][0].normalize();
    icosHedron[k][1].normalize();
    icosHedron[k][2].normalize();
    subd(icosHedron[k][0], icosHedron[k][1], icosHedron[k][2], _d);
  }
}
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------
void World::initStars(
                      const int _a
                     )
{
  // Using the boost random to generate random position and opacity for each star
  boost::random::uniform_int_distribution<> u_random(1, 1000);
  for(int i = 0; i < _a; ++i)
  {
    Vec4 s(u_random(m_rng)/1000.0f * 2 - 1,
           u_random(m_rng)/1000.0f * 2 - 1,
           u_random(m_rng)/1000.0f * 2 - 1,
           u_random(m_rng)/1000.0f * 2 - 1);

    s.normalize();
    // Now we randomise the distance by getting a value that's between the planet and the skybox
    s *= fmod(u_random(m_rng),SKYBOXRADIUS-WORLDRADIUS*ASPHERERADIUS) + 3*WORLDRADIUS*ASPHERERADIUS;
    m_stars.push_back(s);
  }
}
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------
void World::generate_Asteroids()
{
  // Using the boost random to generate random attributes
  // for each asteroid
  boost::random::uniform_int_distribution<> u_random(1, 100);

  // As we don't want to generate asteroids every frame, we add the boost random
  // element to the equation and only generate more asteroids if the randomness
  // gets a value > 95 which should theoretically be about 5% chance every frame
  if(u_random(m_rng)/100.0 > 0.95 && (int)m_asteroids.size() < m_maxAsteroids)
  {
    // Generate a random position for each asteroid (adding 0.01f to each
    // to avoid the unlikely case of each component resulting to 0
    // which would cause problems when we normalise the position.
    Vec4 aPos(u_random(m_rng)/100.0 * 2.0 - 1.0 + 0.01f,
              u_random(m_rng)/100.0 * 2.0 - 1.0 + 0.01f,
              u_random(m_rng)/100.0 * 2.0 - 1.0 + 0.01f);
    aPos.normalize();

    // Setting the direction of the asteroid to be the opposite of it's
    // position, thus the asteroid will be heading towards the planet
    Vec4 aDir = aPos * - 1;

    // We generate
    Vec4 aSide(u_random(m_rng)/100.0,
               u_random(m_rng)/100.0,
               0);

    if(fabs(aPos.m_z) > 0.001f)
      aSide.m_z = -(aSide.m_x*aPos.m_x + aSide.m_y*aPos.m_y) / aPos.m_z;

    // Calculating the up vector the the asteroid by taking the cross product
    // of its position and side vectors
    Vec4 aUp;
    aUp = aSide.cross(aPos);

    // Moving the asteroid to near the skybox
    aPos *= SKYBOXRADIUS;

    // Generate a random scale factor for each asteroid which will be
    // anything between 0.1f to 0.8f
    float size = u_random(m_rng)/100.0 * 0.8f + 0.1f;
    int type = u_random(m_rng)%2;

    // Push the asteroid to the stl vector to have it drawn later
    m_asteroids.push_back(Asteroid(aPos, aDir,
                                 aUp, aSide,
                                 size, fmod(u_random(m_rng)/100.0, 0.04f) + 0.0315f,
                                 size * 150, type));
  }

  // Bind the asteroid texture and loop through the living asteroids
  glBindTexture(GL_TEXTURE_2D, m_aTexId);
  for(int i = 0; i < (int)m_asteroids.size(); ++i)
  {
    // Check if the asteroid still has health left, if so we'll call its
    // drawing function
    if(m_asteroids[i].m_life > 0)
      m_asteroids[i].draw(m_aDisplayList);
    else
    {
      // If not we check the size of the asteroid as bigger asteroids will generate
      // two smaller asteroids (idea is that the asteroid breaks to smaller pieces)
      // TODO: model and implement actually explodable asteroids
      if(m_asteroids[i].m_size > 0.5f)
      {
        for(int j = 0; j < 2; ++j)
        {
          // Set the start position of the new smalle asteroids to be where the bigger
          // one was destroyed, randomise rest of the attributes.
          Vec4 aPos = m_asteroids[i].m_pos;
          aPos.normalize();
          Vec4 new_dir = aPos * - 1;
          Vec4 new_side(u_random(m_rng)/100.0 + 0.01f,
                    u_random(m_rng)/100.0 + 0.01f,
                    0);
          Vec4 new_up = new_side.cross(aPos);

          if(fabs(aPos.m_z) > 0.001)
            new_side.m_z = -(new_side.m_x * aPos.m_x + new_side.m_y * aPos.m_y) / aPos.m_z;

          float new_size = m_asteroids[i].m_size * fmod(u_random(m_rng)/100.0, 0.35f) + 0.25f;

          m_asteroids.push_back(Asteroid(m_asteroids[i].m_pos, new_dir,
                                         new_up, new_side,
                                         new_size, fmod(u_random(m_rng)/100.0, 0.055) + 0.02f,
                                         new_size*150, u_random(m_rng)%2));
        }
      }

      // When an asteroid is destroyed we play the explosion sound and remove it from
      // the stl vector
      Mix_PlayChannel(-1, m_aExplosion, 0);

      m_asteroids.erase(m_asteroids.begin() + i);
    }
  }
  glBindTexture(GL_TEXTURE_2D, 0);
}
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------
void World::partByDist()
{
  // Looping through the asteroids to do the spatial partitioning
  // This is done by checking whether an asteroid has reached the atmosphere
  for(int i = 0; i < (int)m_asteroids.size(); ++i)
    if(fabs(m_asteroids[i].m_pos.length() - WORLDRADIUS*ASPHERERADIUS) < 0.05)
      m_aColIndices.push_back(i);

  // As we're only storing the indices of the asteroids we'll sort the list
  // and call unique to remove duplicate entries as the loop above is not
  // checking whether a certain asteroid has already been added to the list
  m_aColIndices.sort();
  m_aColIndices.unique();
}
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------
void World::genALists()
{
  // Generating the displaylists for both asteroid models
  GLuint id;

  for(int j = 0; j < 2; ++j)
  {
    id = glGenLists(1);
    glNewList(id, GL_COMPILE);
      glBegin(GL_TRIANGLES);
        for(int i = 0; i < (int)m_asteroid[j].m_Ind.size(); i += 9)
        {
          m_asteroid[j].m_Norms[m_asteroid[j].m_Ind[i + 2] - 1].normalGL();
          m_asteroid[j].m_Text[m_asteroid[j].m_Ind[i + 1] - 1].textureGL();
          m_asteroid[j].m_Verts[m_asteroid[j].m_Ind[i] - 1].vertexGL();

          m_asteroid[j].m_Text[m_asteroid[j].m_Ind[i + 4] - 1].textureGL();
          m_asteroid[j].m_Verts[m_asteroid[j].m_Ind[i + 3] - 1].vertexGL();

          m_asteroid[j].m_Text[m_asteroid[j].m_Ind[i + 7] - 1].textureGL();
          m_asteroid[j].m_Verts[m_asteroid[j].m_Ind[i + 6] - 1].vertexGL();
        }
      glEnd();
    glEndList();

    m_aDisplayList.push_back(id);
  }
}
// ---------------------------------------------------------------------------------------
