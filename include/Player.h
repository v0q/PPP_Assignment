#ifndef PLAYER_H
#define PLAYER_H

#ifdef LINUX
  #include <GL/gl.h>
#endif
#ifdef DARWIN
  #include <OpenGL/gl.h>
#endif

#include <SDL2/SDL.h>
#include <vector>
#include <list>

#include "Camera.h"
#include "Audio.h"
#include "Projectile.h"
#include "LoadOBJ.h"
#include "TextureOBJ.h"
#include "Asteroids.h"
#include "NCCA/Vec4.h"

#define PLAYEROFFSET 0.1f
#define PLAYERWIDTH 0.05f
#define PLAYERHEIGHT 0.05f

const int sensitivity = 6000;

class Player
{
  public:
    Player(float _x = 1.0f, float _y = 1.0f, float _z = 1.0f);
    ~Player();

    bool isAlive();
    void drawPlayer();
    void handleMovement(SDL_GameController *_c, Camera &_cam);
    void checkCollisions(std::vector<Asteroid> &io_a, std::list<int> &io_aInd);
    void drawParticles();

    std::vector<Particle> particles;
    int score;

  private:
    void ship();
    void wrapRotation(float &io_a);
    void shoot(SDL_GameController *_c, Vec4 &_cu, Vec4 &_cl);
    void engineFire();

    Vec4 pos, norm;
    Mat4 orientation;

    model m_ship;

    std::vector<Projectile> p;
    std::vector<GLuint> m_displayList;
    Mix_Chunk *a_fire;
    Mix_Music *bgSound;
    float aimDir;
    float rot, turn;
    float xMov, yMov;
    int life, moving;
    GLuint shipTexId, projectileId, particleTexId, engFireTexId;
};

#endif
