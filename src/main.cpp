#include <iostream>
#include <cstdlib>

#include "Sdl_gl.h"
#include "Camera.h"
#include "World.h"
#include "Player.h"

int main()
{
  SDL_GL sdlgl;
  World world;
  Camera cam;
  Player player(0.0f, 0.0f, WORLDRADIUS+PLAYEROFFSET);

  cam.initCamera();
  world.initStars(1500);
  sdlgl.enableLighting();
  glClearColor (0.4, 0.4, 0.4, 0.4);

  while(sdlgl.isActive())
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    cam.updateCamera();

    sdlgl.handleInput(player, cam);

    world.drawStars((cam.eye-cam.look));
    world.drawWorld();
    player.drawPlayer();

    SDL_GL_SwapWindow(sdlgl.win);
  }

  return 0;
}
