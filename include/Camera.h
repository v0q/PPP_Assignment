#ifndef CAMERA_H__
#define CAMERA_H__

#include "Defs.h"
#include "NCCA/Vec4.h"
#define CAMRADIUS 4

class Camera
{
  public:
    // Eye level
    Vec4 eye;
    // Look at
    Vec4 look;
    // Up
    Vec4 up;
    // Left vector
    Vec4 w;
    // Field-of-view
    float fov;
    // Near, far
    float n, f;
    // Aspect ratio
    float a;

    Mat4 orient;

    Camera(): eye(0.0f, 0.0f, 4.0f),
              look(0.0f, 0.0f, 0.0f),
              up(0.0f, 1.0f, 0.0f),
              fov(65.0f),
              n(0.5f), f(200.0f),
              a(SCREENWIDTH / (float)SCREENHEIGHT) {}
    ~Camera() {}

    /*void setEye(float &_x, float &_y, float &_z) { ex = _x; ey = _y; ez = _z; }
    void setUp(float &_x, float &_y, float &_z) { ux = _x; uy = _y; uz = _z; }*/

    void initCamera();
    void updateCamera();
};

#endif
