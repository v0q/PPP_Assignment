#ifndef PLAYER_H__
#define PLAYER_H__

#include <SDL.h>
#include <vector>

#include "Camera.h"
#include "Projectile.h"
#include "NCCA/Vec4.h"
#define PLAYEROFFSET 0.1f
#define PLAYERWIDTH 0.05f
#define PLAYERHEIGHT 0.05f

const int sensitivity = 6000;

class Player
{
  public:
    Player(float _x = 1.0f, float _y = 1.0f, float _z = 1.0f) : pos(_x, _y, _z, 1.0f) {}
    ~Player() { p.clear(); std::vector<Projectile>().swap(p); }

    void drawPlayer();
    void handleMovement(SDL_GameController *_c, Camera &_cam);

  private:
    void cube();
    void wrapRotation(float &io_a);
    void shoot(SDL_GameController *_c, Vec4 &_u, Vec4 &_l);

    Vec4 pos, norm;
    Mat4 orientation;
    std::vector <Projectile> p;
    float aimDir;
    float rot;
    float xMov, yMov;
};

#endif
