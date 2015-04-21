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

  int start = SDL_GetTicks();
  int lastTime = 0;

  while(sdlgl.isActive())
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    frameStart();

    world.drawStars((cam.eye-cam.look));
    world.drawWorld();

    if(player.isAlive())
    {
      player.drawPlayer();
      player.checkCollisions(world.asteroids, world.a_ColIndices);
    }

    cam.updateCamera();

    sdlgl.handleInput(player, cam);

    if(lastTime != (SDL_GetTicks() - start)/1000)
    {
      world.max_asteroids += world.max_asteroids/50 + 1;
      lastTime = (SDL_GetTicks() - start)/1000;
      //std::cout << world.max_asteroids << "s" << "\n";
    }


    frameEnd(GLUT_BITMAP_HELVETICA_18, 1.0, 1.0, 1.0, 0.05, 0.95, player.score);
    SDL_GL_SwapWindow(sdlgl.win);
  }

  return 0;
}
