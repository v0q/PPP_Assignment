/*
 Copyright © 2015 Teemu Lindborg
 SDAGE 1st year 2nd PPP Assignment
*/

#include "Sdl_gl.h"
#include "Camera.h"
#include "World.h"
#include "Player.h"
#include "Asteroids.h"
#include "frames.h"
#include "OrthoText.h"

// ---------------------------------------------------------------------------------------
/// @file main.cpp
/// @brief The main file of the project where the main loop is run and the main
///        objects created and called. Also calls the "main" functions of each
///        object to render the game and handle input etc.
/// @todo Tidy up, make the loop work more like the GL pipeline describes as
///       apparently the normal way to do it is to set the MatrixMode to projection
///       loadIdentity, then load modelview, load identity and render afterwards.
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------
int main()
{
  SDL_GL sdlgl;
  Camera cam;
  World world;
  Player player(0.0f, 0.0f, WORLDRADIUS+PLAYEROFFSET);

  // Initialising the camera, generating stars and enabling gl lightning and
  // texture related stuff, also clearing the screen to a grey color
  cam.initCamera();
  world.initStars(1500);
  sdlgl.enableLighting();
  glClearColor (0.4, 0.4, 0.4, 0.4);

  // Using SDL_GetTicks() to keep track of time passed in the game,
  // this is used later to increase the amount of maximum asteroids
  // that's allowed to be in the scene
  int start = SDL_GetTicks();
  int lastTime = 0;

  while(sdlgl.isActive())
  {
    // Clearing the color and depth buffers and calling the frameStart()
    // function that'll calculate and limit our fps
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    frameStart();

    // Draw the world first
    world.drawWorld();

    // If player is still considered to be alive we draw the player
    // if not pause the background noise that was playing when the
    // ship is flying
    if(player.isAlive())
      player.drawPlayer();
    else
    {
      OrthoText(GLUT_BITMAP_HELVETICA_18, "GAME OVER!", 0.5f, 0.5f);
      Mix_PauseMusic();
    }

    // Updating the camera
    cam.updateCamera();

    // If there are any alive fire particles, render them
    if(player.m_particles.size() > 0)
      player.drawParticles();

    // Checking for collisions between the player, projectiles and asteroids
    if(player.isAlive())
      player.checkCollisions(world.m_asteroids, world.m_aColIndices);

    // Call the function that handles the input and calls
    // the movement handling functions
    sdlgl.handleInput(player, cam);

    // Update the amount of maximum possible asteroids every 1 second
    if(lastTime != (int)(SDL_GetTicks() - start)/1000 && world.m_maxAsteroids < 300)
    {
      world.m_maxAsteroids += world.m_maxAsteroids/50 + 1;
      lastTime = (SDL_GetTicks() - start)/1000;
    }

    // Frame ends here so we call the function that renders the fps and score
    // and calls for SDL_Delay should the fps surpass the limit
    frameEnd(GLUT_BITMAP_HELVETICA_18, 1.0, 1.0, 1.0, 0.05, 0.95, player.m_score);
    SDL_GL_SwapWindow(sdlgl.m_win);
  }

  // As we're using an object for the window and context creation
  // Before the program is closed the destructor of sdlgl object
  // is called which handles the cleaning up

  return 0;
}
// ---------------------------------------------------------------------------------------
