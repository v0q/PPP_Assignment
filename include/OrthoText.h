/*
 Copyright © 2015 Teemu Lindborg
 SDAGE 1st year 2nd PPP Assignment
 Code stripped down from the frames.h code
 © by Toby Howard
*/

#ifndef ORTHOTEXT_H
#define ORTHOTEXT_H

// ---------------------------------------------------------------------------------------
/// @file OrthoText.h
/// @brief Structure to hold and functions to load OBJ-file data and freeing up the used
///        memory in the end.
/// @version 2.1
/// @author Toby Howard. toby.howardy@manchester.ac.uk. Stripped down by Teemu Lindborg
/// @date 03/01/13
/// Revision History:
///   -
/// @todo Go through the snippet and understand it completely to be able to comment this
///       properly
// ---------------------------------------------------------------------------------------

#ifdef LINUX
  #include <GL/glut.h>
#endif
#ifdef DARWIN
  #include <glut/glut.h>
#endif

#include <string>

void OrthoText(
               void *_font,
               const std::string &_str,
               const GLfloat _x,
               const GLfloat _y
              )
{
  const char *ch;
  GLint matrixMode;
  GLboolean lightingOn;

  lightingOn = glIsEnabled(GL_LIGHTING);
  if (lightingOn) glDisable(GL_LIGHTING);

  glGetIntegerv(GL_MATRIX_MODE, &matrixMode);

  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0.0, 1.0, 0.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

      glLoadIdentity();
      glPushAttrib(GL_COLOR_BUFFER_BIT);
        glColor3f(1.0f, 1.0f, 1.0f);
        glRasterPos3f(_x, _y, 0.0);
        for(ch = _str.c_str(); *ch; ch++)
        {
          glutBitmapCharacter(_font, (int)*ch);
        }
      glPopAttrib();

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);

  glPopMatrix();
  glMatrixMode(matrixMode);

  if (lightingOn) glEnable(GL_LIGHTING);
}

#endif
