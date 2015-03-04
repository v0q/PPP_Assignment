#ifndef PLAYER_H__
#define PLAYER_H__

#include "NCCA/Vec4.h"
#define PLAYEROFFSET 0.1f

class Player
{
  public:
    Vec4 pos, norm;
    float rot;

    Player(float _x = 1.0f, float _y = 1.0f, float _z = 1.0f) : pos(_x, _y, _z, 1.0f), rot(0.0f) {}
    ~Player();

    void drawPlayer();
    void handleMovement();
  private:
    void cube();
    void wrapRotation(float &io_a);
};

#endif
