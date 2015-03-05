#ifndef UNIVERSE_H__
#define UNIVERSE_H__

#include "NCCA/Vec4.h"

class Universe
{
  public:
    Vec4 v1, v2, r;
    float angle, rot;
    Universe(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f) : v1(_x, _y, _z), v2(_x, _y, _z) {}

};

#endif
