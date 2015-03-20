#ifndef WORLD_H__
#define WORLD_H__

#include <vector>
#include <list>
#include <string>
#include <cmath>
#include <OpenGL/gl.h>

#include "NCCA/Vec4.h"
#include "Asteroids.h"

#define SKYBOXRADIUS 15

class World
{
  public:
    World() : max_asteroids(500) { planet(); atmosphere(); skybox(); }
    ~World() { stars.clear();
               std::vector<Vec4>().swap(stars);
               w_displayList.clear();
               std::vector<GLuint>().swap(w_displayList);
               asteroids.clear();
               std::vector<Asteroid>().swap(asteroids);
               a_ColIndices.clear();
               std::list<int>().swap(a_ColIndices); }
    void initStars(int _a);
    void drawStars(Vec4 _c) const;
    void drawWorld();
    void subd(Vec4 &_a, Vec4 &_b, Vec4 &_c, int _d, int _ndir) const;

    std::vector<Asteroid> asteroids;
    std::list<int> a_ColIndices;

  private:
    void planet();
    void atmosphere();
    void skybox();
    void generate_Asteroids();
    void tSphere(int _d, int _ndir) const;
    void drawTriangle(Vec4 &_a, Vec4 &_b, Vec4 &_c, int _ndir) const;
    void partByDist();

    std::vector<Vec4> stars;
    std::vector<GLuint> w_displayList;
    int max_asteroids;
};

#endif
