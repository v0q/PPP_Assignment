#include "Defs.h"
#include "Sdl_gl.h"
#include "World.h"

SDL_GL::SDL_GL()
{
  if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
  {
    SDLErrorExit("Couldn't initialise SDL");
  }

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

  act = true;
}

SDL_GL::~SDL_GL()
{
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
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glColor3f(1,1,0);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);
}

bool SDL_GL::isActive() const
{
  return act;
}

void SDL_GL::handleInput(Player &_player)
{
  SDL_Event event;
  const Uint8 *keystate = SDL_GetKeyboardState(NULL);
  static int i = 70, j = 53;


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
          case SDLK_w : glPolygonMode(GL_FRONT_AND_BACK,GL_LINE); break;
          case SDLK_s : glPolygonMode(GL_FRONT_AND_BACK,GL_FILL); break;
          default : break;
        } // end of key process
      } // end of keydown

      default : break;
    } // end of event switch
  } // end of poll events

  if(keystate[SDL_SCANCODE_UP])
    i = (i + 1) % MOVEPRECISION;
  else if(keystate[SDL_SCANCODE_DOWN])
    i = (i - 1) % MOVEPRECISION;
  if(keystate[SDL_SCANCODE_LEFT])
    j = (j + 1) % MOVEPRECISION;
  else if(keystate[SDL_SCANCODE_RIGHT])
    j = (j - 1) % MOVEPRECISION;

  _player.pos = Vec4::sphericalCoords(i, j, PLAYEROFFSET);
}
