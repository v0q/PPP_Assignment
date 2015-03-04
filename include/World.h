#ifndef WORLD_H__
#define WORLD_H__

#include <string>
#include <cmath>
#include "Camera.h"
#include "Player.h"
#include "Universe.h"

class World
{
  public:
    World();
    ~World();
    void drawWorld(Universe _u) const;
    void updateCamera();
    void subd(Vec4 &_a, Vec4 &_b, Vec4 &_c, int _d) const;

    Camera cam;

  private:
    void planet() const;
    void atmosphere() const;
    void sphere(float _radius) const;
    void tSphere(int _i) const;
    void drawTriangle(Vec4 &_a, Vec4 &_b, Vec4 &_c) const;

};

#endif
