#ifndef WORLD_H__
#define WORLD_H__

#ifdef LINUX
  #include <GL/gl.h>
#endif
#ifdef DARWIN
  #include <OpenGL/gl.h>
#endif

#include <vector>
#include <list>
#include <string>
#include <cmath>
#include <SDL2/SDL_mixer.h>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>

#include "Asteroids.h"
#include "Planet.h"
#include "LoadOBJ.h"
#include "NCCA/Vec4.h"

#define SKYBOXRADIUS 15

class World
{
  public:
    World();
    ~World();
    void initStars(int _a);
    void drawStars(Vec4 _c) const;
    void drawWorld();
    void subd(Vec4 &_a, Vec4 &_b, Vec4 &_c, int _d, int _ndir) const;

    std::vector<Asteroid> asteroids;
    std::list<int> a_ColIndices;
    int max_asteroids;

  private:
    void drawPlanet();
    void atmosphere();
    void skybox();
    void generate_Asteroids();
    void genALists();
    void tSphere(int _d, int _ndir) const;
    void drawTriangle(Vec4 &_a, Vec4 &_b, Vec4 &_c, int _ndir) const;
    void partByDist();

    Planet m_planet;

    // Skybox model
    model m_skybox;

    // Asteroid models
    model m_asteroid[2];

    std::vector<Vec4> stars;
    std::vector<GLuint> w_displayList;
    std::vector<GLuint> a_displayList;

    Mix_Chunk *a_explosion, *a_bgmusic;
    GLuint skyBoxTexId, aTexId;


    boost::mt19937 rng;
};

#endif
