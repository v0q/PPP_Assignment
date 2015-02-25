#ifndef CAMERA_H__
#define CAMERA_H__

#include "Defs.h"

class Camera
{
  public:
    // Eye level
    float ex, ey, ez;
    // Look at
    float lx, ly, lz;
    // Up
    float ux, uy, uz;
    // Field-of-view
    float fov;
    // Near, far
    float n, f;
    // Aspect ratio
    float a;

    Camera(): ex(1.0f), ey(1.0f), ez(4.0f),
              lx(0.0f), ly(0.0f), lz(0.0f),
              ux(0.0f), uy(1.0f), uz(0.0f),
              fov(65.0f),
              n(0.5f), f(200.0f),
              a(SCREENWIDTH / (float)SCREENHEIGHT) {}

    void setEye(float &_x, float &_y, float &_z) { ex = _x; ey = _y; ez = _z; }
    void setUp(float &_x, float &_y, float &_z) { ux = _x; uy = _y; uz = _z; }

};

#endif
