#include <SDL.h>

#include "NCCA/GLFunctions.h"
#include "Defs.h"
#include "Sdl_gl.h"

SDL_GL::SDL_GL()
{
  if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
    SDLErrorExit("Couldn't initialise SDL");

  if(SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER) == -1)
    SDLErrorExit("Couldn't initialise SDL controller");

  win = SDL_CreateWindow("SS", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREENWIDTH, SCREENHEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

  if(!win)
  {
    SDLErrorExit("Couldn't create SDL window");
  }

  gl = createOpenGLContext();
  if(!gl)
  {
    SDLErrorExit("Problem creating OpenGL context");
  }

  controller = NULL;

  for(int i = 0; i < SDL_NumJoysticks(); i++)
  {
    if((controller = SDL_GameControllerOpen(i)))
      break;
  }

  act = true;
}

SDL_GL::~SDL_GL()
{
  if(!controller)
    SDL_GameControllerClose(controller);
  SDL_Quit();
}

void SDL_GL::SDLErrorExit(const std::string &_msg)
{
  std::cerr<<_msg<<"\n";
  std::cerr<<SDL_GetError()<<"\n";
  SDL_Quit();
  exit(EXIT_FAILURE);
}

SDL_GLContext SDL_GL::createOpenGLContext()
{
  // Request an opengl 3.2 context first we setup our attributes, if you need any
  // more just add them here before the call to create the context
  // SDL doesn't have the ability to choose which profile at this time of writing,
  // but it should default to the core profile
  // for some reason we need this for mac but linux crashes on the latest nvidia drivers
  // under centos
  #ifdef DARWIN
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
  #endif
  // set multi sampling else we get really bad graphics that alias
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
  SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,2);
  // Turn on double buffering with a 24bit Z buffer.
  // You may need to change this to 16 or 32 for your system
  // on mac up to 32 will work but under linux centos build only 16
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
  // enable double buffering (should be on by default)
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  //
  return SDL_GL_CreateContext(win);
}

void SDL_GL::enableLighting() const
{
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  GLfloat mat_specular[] = { 0.5, 0.5, 0.5, 1.0 };
  GLfloat mat_shininess[] = { 100.0 };
  GLfloat light_position[] = { 0.5, 0.75, 1.5, 0.0 };
  GLfloat light_position2[] = { 0.0, 0.0, -3, 0.0 };
  glShadeModel (GL_SMOOTH);

  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glLightfv(GL_LIGHT1, GL_POSITION, light_position2);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT1);
  glColor3f(1,1,0);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);
}

bool SDL_GL::isActive() const
{
  return act;
}

void SDL_GL::handleInput(Player &io_p, Camera &_cam)
{
  SDL_Event event;

  while( SDL_PollEvent(&event) )
  {
    switch (event.type)
    {
      // this is the window x being clicked.
      case SDL_QUIT : act = false; break;

      // now we look for a keydown event
      case SDL_KEYDOWN:
      {
        switch( event.key.keysym.sym )
        {
          // if it's the escape key act
          case SDLK_ESCAPE : act = false; break;
          case SDLK_k : glPolygonMode(GL_FRONT_AND_BACK,GL_LINE); break;
          case SDLK_l : glPolygonMode(GL_FRONT_AND_BACK,GL_FILL); break;
          default : break;
        } // end of key process
      } // end of keydown

      default : break;
    } // end of event switch
  } // end of poll events

  if(io_p.isAlive())
    io_p.handleMovement(controller, _cam);
}
