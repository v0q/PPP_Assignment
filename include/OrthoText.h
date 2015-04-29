#ifdef LINUX
  #include <GL/glut.h>
#endif
#ifdef DARWIN
  #include <glut/glut.h>
#endif

#include <string>

void OrthoText(void *font, const std::string &_str, GLfloat x, GLfloat y)
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
        glRasterPos3f(x, y, 0.0);
        for(ch = _str.c_str(); *ch; ch++)
        {
          glutBitmapCharacter(font, (int)*ch);
        }
      glPopAttrib();

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);

  glPopMatrix();
  glMatrixMode(matrixMode);

  if (lightingOn) glEnable(GL_LIGHTING);
  std::cout << "SHOULD PRINT OUT THE THING!\n";
}
