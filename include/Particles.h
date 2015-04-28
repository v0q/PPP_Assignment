#ifndef PARTICLES_H
#define PARTICLES_H

#include <OpenGL/gl.h>
#include "NCCA/Vec4.h"

class Particle
{
  public:
    Particle(Vec4 &_p, int _l = 0) : pos(_p), dir(0, 1, 0), life(0), max_life(_l) { moveX = 0.01 * (std::rand()/(float)RAND_MAX * 2 - 1);
                                                                                    moveY = 0.01 * (std::rand()/(float)RAND_MAX * 2 - 1);
                                                                                    moveZ = 0.01 * (std::rand()/(float)RAND_MAX * 2 - 1); }
    ~Particle() {}

    void draw() const;
    void move();

    Vec4 pos;
    Vec4 dir;
    int life, max_life;
    float moveX, moveY, moveZ;
};

#endif
