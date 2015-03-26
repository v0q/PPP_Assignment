#ifndef PLAYER_H__
#define PLAYER_H__

#include <OpenGL/gl.h>
#include <SDL.h>
#include <vector>
#include <list>

#include "Camera.h"
#include "Projectile.h"
#include "LoadOBJ.h"
#include "Asteroids.h"
#include "NCCA/Vec4.h"

#define PLAYEROFFSET 0.1f
#define PLAYERWIDTH 0.05f
#define PLAYERHEIGHT 0.05f

const int sensitivity = 6000;

class Player
{
  public:
    Player(float _x = 1.0f, float _y = 1.0f, float _z = 1.0f) : score(0), pos(_x, _y, _z, 1.0f), life(100) { loadModel("models/ss.obj", mVerts, mNorms, mText, mInd); ship(); }
    ~Player() { p.clear();
                std::vector<Projectile>().swap(p);
                mVerts.clear();
                std::vector<Vec4>().swap(mVerts);
                mNorms.clear();
                std::vector<Vec4>().swap(mNorms);
                mText.clear();
                std::vector<Vec4>().swap(mText);
                mInd.clear();
                std::vector<int>().swap(mInd); }

    bool isAlive();
    void drawPlayer();
    void handleMovement(SDL_GameController *_c, Camera &_cam);
    void checkCollisions(std::vector<Asteroid> &io_a, std::list<int> &io_aInd);

    int score;

  private:
    void ship();
    void wrapRotation(float &io_a);
    void shoot(SDL_GameController *_c);

    Vec4 pos, norm;
    Mat4 orientation;
    std::vector<Vec4> mVerts;
    std::vector<Vec4> mNorms;
    std::vector<Vec4> mText;
    std::vector<int> mInd;
    std::vector<Projectile> p;
    std::vector<GLuint> m_displayList;
    float aimDir;
    float rot, turn;
    float xMov, yMov;
    int life;
    GLuint id;
};

#endif
