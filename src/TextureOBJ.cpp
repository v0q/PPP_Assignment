/*
 Copyright © 2015 Teemu Lindborg
 SDAGE 1st year 2nd PPP Assignment
*/

#ifdef LINUX
  #include <GL/gl.h>
#endif
#ifdef DARWIN
  #include <OpenGL/gl.h>
#endif

#include <SDL2/SDL_image.h>

#include "TextureOBJ.h"

// ---------------------------------------------------------------------------------------
/// @file TextureOBJ.cpp
/// @brief Implementation of the texture loading function
// ---------------------------------------------------------------------------------------

void loadTexture(const std::string &_n, GLuint &o_id)
{
  SDL_Surface *texture;
  if(!(texture = IMG_Load(_n.c_str())))
  {
    std::cerr << "Couldn't load texture " << _n << "\n";
    exit(0);
  }

  GLint mode = ((int)texture->format->BytesPerPixel == 4 ? GL_RGBA : GL_RGB);

  glGenTextures(1, &o_id);
  glBindTexture(GL_TEXTURE_2D, o_id);
  glTexImage2D(GL_TEXTURE_2D, 0, mode, texture->w, texture->h, 0, mode, GL_UNSIGNED_BYTE, texture->pixels);

  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

  SDL_FreeSurface(texture);
}
