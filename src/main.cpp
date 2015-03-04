#include <iostream>
#include <cstdlib>

#include "Sdl_gl.h"
#include "Universe.h"
#include "World.h"
#include "Player.h"

int main()
{
  SDL_GL sdlgl;
  World world;
  Universe rotation(0.0f, 0.0f, 0.0f);
  Player player(0.0f, 0.0f, 0.0f);

  world.updateCamera();
  sdlgl.enableLighting();
  glClearColor (0.4, 0.4, 0.4, 0.4);

  while(sdlgl.isActive())
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    world.drawWorld(rotation);
    player.drawPlayer();

    sdlgl.handleInput(player, rotation);

    glPushMatrix();
      glLineWidth(3);
      glBegin(GL_LINE_STRIP);
        glColor3f(1,1,1);
        glVertex3f(0,0,0);
        glVertex3f(0,1,0);
      glEnd();
      glBegin(GL_LINE_STRIP);
        glColor3f(0,0,0);
        glVertex3f(0,0,0);
        glVertex3f(1,0,0);
      glEnd();
      glBegin(GL_LINE_STRIP);
        glColor3f(1,0,0);
        glVertex3f(0,0,0);
        glVertex3f(0,0,1);
      glEnd();
      glLineWidth(1);
    glPopMatrix();

    SDL_GL_SwapWindow(sdlgl.win);
  }

  return 0;
}
