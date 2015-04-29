#ifndef WORLD_H__
#define WORLD_H__

#include <vector>
#include <list>
#include <string>
#include <cmath>
#include <OpenGL/gl.h>
#include <SDL2/SDL_mixer.h>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>

#include "Asteroids.h"
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
    void planet();
    void atmosphere();
    void skybox();
    void generate_Asteroids();
    void genALists();
    void tSphere(int _d, int _ndir) const;
    void drawTriangle(Vec4 &_a, Vec4 &_b, Vec4 &_c, int _ndir) const;
    void partByDist();

    // Skybox model
    std::vector<Vec4> skybox_Verts;
    std::vector<Vec4> skybox_Norms;
    std::vector<Vec4> skybox_Text;
    std::vector<int> skybox_Ind;

    // Planet model
    std::vector<Vec4> planet_Verts;
    std::vector<Vec4> planet_Norms;
    std::vector<Vec4> planet_Text;
    std::vector<int> planet_Ind;

    // Asteroid models
    std::vector<Vec4> asteroid_Verts[2];
    std::vector<Vec4> asteroid_Norms[2];
    std::vector<Vec4> asteroid_Text[2];
    std::vector<int> asteroid_Ind[2];

    std::vector<Vec4> stars;
    std::vector<GLuint> w_displayList;
    std::vector<GLuint> a_displayList;

    Mix_Chunk *a_explosion, *a_bgmusic;
    GLuint skyBoxTexId, aTexId;


    boost::random::mt11213b rng;
    //boost::mt19937 rng;
};

#endif
