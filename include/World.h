#ifndef WORLD_H__
#define WORLD_H__

#include <string>
#include <cmath>
#include "Player.h"

class World
{
  public:
    World();
    ~World();
    void drawWorld() const;
    void subd(Vec4 &_a, Vec4 &_b, Vec4 &_c, int _d) const;

  private:
    void planet() const;
    void atmosphere() const;
    void tSphere(int _d) const;
    void drawTriangle(Vec4 &_a, Vec4 &_b, Vec4 &_c) const;

};

#endif
