#ifndef WORLD_H__
#define WORLD_H__

#include <string>
#include <cmath>
#include "Camera.h"
#include "Player.h"

class World
{
  public:
    World();
    ~World();
    void drawWorld() const;
    void updateCamera();
    Camera cam;

  private:
    void planet() const;

};

#endif
