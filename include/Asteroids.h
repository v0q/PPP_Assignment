#ifndef ASTEROIDS_H__
#define ASTEROIDS_H__

#include "Defs.h"
#include "NCCA/Vec4.h"

class Asteroid
{
  public:
    Asteroid(Vec4 &_p, Vec4 &_d,
             float _s, float _sp,
             float _l) :
             pos(_p),
             dir(_d),
             size(_s), speed(_sp),
             rot(0.0), life(_l) {}
    ~Asteroid() {}

    Vec4 pos, dir;
    float size, speed, rot;
    int life;

    void draw();
    void move();
};

#endif
