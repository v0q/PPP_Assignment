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
               dir(_d), life(0), max_life(_ml) { loadModel("models/projectile.obj", mVerts, mNorms, mText, mInd);}
    ~Projectile() {}
    void drawProjectile(int num_it, Vec4 &_cu, Vec4 &_cl);

    Vec4 pos, up, left, normal;
    float dir;
    int life, max_life;

  private:
    std::vector<Vec4> mVerts;
    std::vector<Vec4> mNorms;
    std::vector<Vec4> mText;
    std::vector<int> mInd;
};

#endif
