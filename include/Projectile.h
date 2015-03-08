#ifndef PROJECTILE_H__
#define PROJECTILE_H__

#include "NCCA/Vec4.h"

class Projectile
{
  public:
    Projectile(float _px, float _py, float _pz,
               float _dx, float _dy, float _dz) :
               pos(_px, _py, _pz), dir(_dx, _dy, _dz), life(75), speed(0.05) {}
    ~Projectile() {}
    Vec4 pos, dir;
    int life;
    float speed;

  private:
};

#endif
