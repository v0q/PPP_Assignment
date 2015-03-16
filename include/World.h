#ifndef WORLD_H__
#define WORLD_H__

#include <string>
#include <cmath>
#include "Player.h"

#define SKYBOXRADIUS 15

class World
{
  public:
    World() {}
    ~World() { stars.clear(); std::vector<Vec4>().swap(stars); }
    void initStars(int _a);
    void drawStars(Vec4 _c) const;
    void drawWorld() const;
    void subd(Vec4 &_a, Vec4 &_b, Vec4 &_c, int _d, int _dir) const;

  private:
    void planet() const;
    void atmosphere() const;
    void skybox() const;
    void tSphere(int _d, int _dir) const;
    void drawTriangle(Vec4 &_a, Vec4 &_b, Vec4 &_c, int _dir) const;

    std::vector <Vec4> stars;

};

#endif
