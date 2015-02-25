#ifndef SDL_GL_H__
#define SDL_GL_H__

#include <SDL.h>
#include <OpenGL/gl.h>
#include <iostream>

#include "Player.h"

class SDL_GL
{
  public:
    SDL_Window *win;

    SDL_GL();
    ~SDL_GL();
    void SDLErrorExit(const std::string &_msg);
    void enableLighting() const;

    bool isActive() const;
    void handleInput(Player &_player);

  private:
    SDL_GLContext gl;
    SDL_GLContext createOpenGLContext();
    bool act;
};

#endif
