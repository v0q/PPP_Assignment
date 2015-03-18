#ifndef PROJECTILE_H__
#define PROJECTILE_H__

#include "NCCA/Vec4.h"

#define PROJECTILESPEED 0.1

class Projectile
{
  public:
    Projectile(float _px, float _py, float _pz,
               Vec4 &_u, Vec4 &_l,
               float _nx, float _ny, float _nz,
               float _d) :
               pos(_px, _py, _pz),
               up(_u), left(_l),
               normal(_nx, _ny, _nz),
               dir(_d), life(35) {}
    ~Projectile() {}
    Vec4 pos, up, left, normal;
    float dir;
    int life;

  private:
};

#endif
