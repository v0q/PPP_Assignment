#include <iostream>
#include <cstdlib>

#include "Sdl_gl.h"
#include "World.h"
#include "Player.h"

int main()
{
  SDL_GL sdlgl;
  World world;
  Player player(0.0f, 0.0f, 2.0f);

  world.updateCamera();
  sdlgl.enableLighting();

  while(sdlgl.isActive())
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    world.drawWorld();
    player.drawPlayer();

    sdlgl.handleInput(player);

    SDL_GL_SwapWindow(sdlgl.win);
  }

  return 0;
}
