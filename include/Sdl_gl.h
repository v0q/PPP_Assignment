#ifndef SDL_GL_H__
#define SDL_GL_H__

#ifdef LINUX
  #include <GL/gl.h>
#endif
#ifdef DARWIN
  #include <OpenGL/gl.h>
#endif

#include <SDL2/SDL.h>
#include <iostream>

#include "Camera.h"
#include "Player.h"
#include "World.h"

class SDL_GL
{
  public:
    SDL_Window *win;
    SDL_GameController *controller;

    SDL_GL();
    ~SDL_GL();
    void SDLErrorExit(const std::string &_msg);
    void enableLighting() const;

    bool isActive() const;
    void handleInput(Player &io_p, Camera &_cam);

  private:
    SDL_GLContext gl;
    SDL_GLContext createOpenGLContext();
    bool act;
};

#endif
