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

void Mat4::operator *=(const Mat4 &_rhs)
{
  m_00 = m_m[0][0] * _rhs.m_m[0][0] + m_m[0][1] * _rhs.m_m[1][0] + m_m[0][2] * _rhs.m_m[2][0] +
         m_m[0][3] * _rhs.m_m[3][0];
  m_01 = m_m[0][0] * _rhs.m_m[0][1] + m_m[0][1] * _rhs.m_m[1][1] + m_m[0][2] * _rhs.m_m[2][1] +
         m_m[0][3] * _rhs.m_m[3][1];
  m_02 = m_m[0][0] * _rhs.m_m[0][2] + m_m[0][1] * _rhs.m_m[1][2] + m_m[0][2] * _rhs.m_m[2][2] +
         m_m[0][3] * _rhs.m_m[3][2];
  m_03 = m_m[0][0] * _rhs.m_m[0][3] + m_m[0][1] * _rhs.m_m[1][3] + m_m[0][2] * _rhs.m_m[2][3] +
         m_m[0][3] * _rhs.m_m[3][3];

  m_10 = m_m[1][0] * _rhs.m_m[0][0] + m_m[1][1] * _rhs.m_m[1][0] + m_m[1][2] * _rhs.m_m[2][0] +
         m_m[1][3] * _rhs.m_m[3][0];
  m_11 = m_m[1][0] * _rhs.m_m[0][1] + m_m[1][1] * _rhs.m_m[1][1] + m_m[1][2] * _rhs.m_m[2][1] +
         m_m[1][3] * _rhs.m_m[3][1];
  m_12 = m_m[1][0] * _rhs.m_m[0][2] + m_m[1][1] * _rhs.m_m[1][2] + m_m[1][2] * _rhs.m_m[2][2] +
         m_m[1][3] * _rhs.m_m[3][2];
  m_13 = m_m[1][0] * _rhs.m_m[0][3] + m_m[1][1] * _rhs.m_m[1][3] + m_m[1][2] * _rhs.m_m[2][3] +
         m_m[1][3] * _rhs.m_m[3][3];

  m_20 = m_m[2][0] * _rhs.m_m[0][0] + m_m[2][1] * _rhs.m_m[1][0] + m_m[2][2] * _rhs.m_m[2][0] +
         m_m[2][3] * _rhs.m_m[3][0];
  m_21 = m_m[2][0] * _rhs.m_m[0][1] + m_m[2][1] * _rhs.m_m[1][1] + m_m[2][2] * _rhs.m_m[2][1] +
         m_m[2][3] * _rhs.m_m[3][1];
  m_22 = m_m[2][0] * _rhs.m_m[0][2] + m_m[2][1] * _rhs.m_m[1][2] + m_m[2][2] * _rhs.m_m[2][2] +
         m_m[2][3] * _rhs.m_m[3][2];
  m_23 = m_m[2][0] * _rhs.m_m[0][3] + m_m[2][1] * _rhs.m_m[1][3] + m_m[2][2] * _rhs.m_m[2][3] +
         m_m[2][3] * _rhs.m_m[3][3];

  m_30 = m_m[3][0] * _rhs.m_m[0][0] + m_m[3][1] * _rhs.m_m[1][0] + m_m[3][2] * _rhs.m_m[2][0] +
         m_m[3][3] * _rhs.m_m[3][0];
  m_31 = m_m[3][0] * _rhs.m_m[0][1] + m_m[3][1] * _rhs.m_m[1][1] + m_m[3][2] * _rhs.m_m[2][1] +
         m_m[3][3] * _rhs.m_m[3][1];
  m_32 = m_m[3][0] * _rhs.m_m[0][2] + m_m[3][1] * _rhs.m_m[1][2] + m_m[3][2] * _rhs.m_m[2][2] +
         m_m[3][3] * _rhs.m_m[3][2];
  m_33 = m_m[3][0] * _rhs.m_m[0][3] + m_m[3][1] * _rhs.m_m[1][3] + m_m[3][2] * _rhs.m_m[2][3] +
         m_m[3][3] * _rhs.m_m[3][3];
}

void Mat4::normalize()
{
  float c_1, c_2, c_3, c_4;
  c_1 = m_m[0][0] + m_m[1][0] + m_m[2][0] + m_m[3][0];
  c_2 = m_m[0][1] + m_m[1][1] + m_m[2][1] + m_m[3][1];
  c_3 = m_m[0][2] + m_m[1][2] + m_m[2][2] + m_m[3][2];
  c_4 = m_m[0][3] + m_m[1][3] + m_m[2][3] + m_m[3][3];

  m_00 /= c_1;
  m_01 /= c_2;
  m_02 /= c_3;
  m_03 /= c_4;
  m_10 /= c_1;
  m_11 /= c_2;
  m_12 /= c_3;
  m_13 /= c_4;
  m_20 /= c_1;
  m_21 /= c_2;
  m_22 /= c_3;
  m_23 /= c_4;
  m_30 /= c_1;
  m_31 /= c_2;
  m_32 /= c_3;
  m_33 /= c_4;
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
