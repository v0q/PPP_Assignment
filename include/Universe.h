#ifndef UNIVERSE_H__
#define UNIVERSE_H__

#include "NCCA/Vec4.h"
#include "NCCA/Mat4.h"

class Universe
{
  public:
    Mat4 transformation;
    float rX, rY, rZ;
    Universe(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f) : rX(_x), rY(_y), rZ(_z) {}

    static void arcBallVector(int _x, int _y, float *v);

    struct Quaternion
    {
      float w;
      float x;
      float y;
      float z;
    } Quaternion;
};

#endif
