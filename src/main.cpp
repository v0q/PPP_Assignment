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
  sdlgl.enableLighting();
  glClearColor (0.4, 0.4, 0.4, 0.4);

  while(sdlgl.isActive())
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    cam.updateCamera();
    world.drawWorld();

    player.drawPlayer();
    sdlgl.handleInput(player, cam);


    glPushMatrix();
      glPointSize(15);
      glBegin(GL_POINTS);
        glColor3f(0,1,0);
        glVertex3f(0,0,2.2f);
      glEnd();
    glPopMatrix();
    /*glPushMatrix();
      glLineWidth(3);
      glBegin(GL_LINE_STRIP);
        glColor3f(1,0,0);
        glVertex3f(0,0,0);
        glVertex3f(0,1,0);
      glEnd();
      glBegin(GL_LINE_STRIP);
        glColor3f(0,1,0);
        glVertex3f(0,0,0);
        glVertex3f(1,0,0);
      glEnd();
      glBegin(GL_LINE_STRIP);
        glColor3f(0,0,1);
        glVertex3f(0,0,0);
        glVertex3f(0,0,1);
      glEnd();
      glLineWidth(1);
    glPopMatrix();*/

    SDL_GL_SwapWindow(sdlgl.win);
  }

  return 0;
}
