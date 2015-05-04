#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <vector>

#include "LoadOBJ.h"
#include "Particles.h"
#include "NCCA/Vec4.h"

#define PROJECTILESPEED 0.1

class Projectile
{
  public:
    Projectile(float _px, float _py, float _pz,
               Vec4 _u, Vec4 _l,
               float _nx, float _ny, float _nz,
               float _d, float _ml) :
               pos(_px, _py, _pz),
               up(_u), left(_l),
               normal(_nx, _ny, _nz),
               dir(_d), life(0), max_life(_ml) {}
    ~Projectile() {}
    void drawProjectile(int num_it, const Vec4 &_cu, const Vec4 &_cl);

    Vec4 pos, up, left, normal;
    float dir;
    int life, max_life;
};

#endif
