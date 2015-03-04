#ifndef SDL_GL_H__
#define SDL_GL_H__

#include <SDL.h>
#include <OpenGL/gl.h>
#include <iostream>

#include "Universe.h"
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
    void handleInput(Player &io_p, Universe &io_u);

  private:
    SDL_GLContext gl;
    SDL_GLContext createOpenGLContext();
    bool act;
};

#endif
