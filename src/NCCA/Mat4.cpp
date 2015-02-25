#include <cstring> // For memcpy
#include "NCCA/Mat4.h"

#ifdef LINUX
  #include <GL/gl.h>
#endif
#ifdef DARWIN
  #include <OpenGL/gl.h>
#endif

Mat4::Mat4(float _s)
{
  memset(&m_m, 0, sizeof(m_m));
  m_00 = _s;
  m_11 = _s;
  m_22 = _s;
  m_33 = _s;
}

Mat4::Mat4(const Mat4 &_rhs)
{
  memcpy(m_m, &_rhs.m_m, sizeof(m_m));
}

void Mat4::identity()
{
  memset(&m_m, 0, sizeof(m_m));
  m_00 = 1.0f;
  m_11 = 1.0f;
  m_22 = 1.0f;
  m_33 = 1.0f;
}

void Mat4::loadProjection() const
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glMultMatrixf(m_openGL);
  glMatrixMode(GL_MODELVIEW);
}

void Mat4::loadModelView() const
{
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glMultMatrixf(m_openGL);
}
