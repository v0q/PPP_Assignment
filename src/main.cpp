#include <iostream>
#include <cstdlib>

#include "Sdl_gl.h"
#include "Camera.h"
#include "World.h"
#include "Player.h"
#include "Asteroids.h"
#include "frames.h"

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

  std::srand(time(NULL));

  while(sdlgl.isActive())
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    frameStart();

    cam.updateCamera();

    world.drawStars((cam.eye-cam.look));
    world.drawWorld();

    if(player.isAlive())
    {
      player.drawPlayer();
      player.checkCollisions(world.asteroids, world.a_ColIndices);
    }

    sdlgl.handleInput(player, cam);

    frameEnd(GLUT_BITMAP_HELVETICA_18, 1.0, 1.0, 1.0, 0.05, 0.95, player.score);
    SDL_GL_SwapWindow(sdlgl.win);
  }

  return 0;
}
