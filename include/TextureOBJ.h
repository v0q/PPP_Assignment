/*
 Copyright © 2015 Teemu Lindborg
 SDAGE 1st year 2nd PPP Assignment
*/

#ifndef TEXTUREOBJ_H
#define TEXTUREOBJ_H

// ---------------------------------------------------------------------------------------
/// @file TextureOBJ.h
/// @brief Function that loads a texture to a provided GLuint
/// @version 1.0
/// @author Teemu Lindborg
/// @date 03/05/15
/// Revision History:
///   -
/// @todo Use namespaces here maybe. Name of the files might be misleading at the moment
///       as this is not only used to texture objs
// ---------------------------------------------------------------------------------------

#ifdef LINUX
  #include <GL/gl.h>
#endif
#ifdef DARWIN
  #include <OpenGL/gl.h>
#endif

#include <iostream>

// ---------------------------------------------------------------------------------------
/// @brief Loads the texture and cleans up afterwards
/// @param[in] _n Path to the texture to be loaded
/// @param[out] o_id GLuint that the texture data will be loaded in to
// ---------------------------------------------------------------------------------------
void loadTexture(const std::string &_n, GLuint &o_id);

#endif // end of TEXTUREOBJ_H
