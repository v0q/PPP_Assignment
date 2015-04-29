#ifndef TEXTUREOBJ_H
#define TEXTUREOBJ_H

#ifdef LINUX
  #include <GL/gl.h>
#endif
#ifdef DARWIN
  #include <OpenGL/gl.h>
#endif

#include <iostream>

void loadTexture(const std::string &_n, GLuint &_id);

#endif
