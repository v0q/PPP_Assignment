#include "NCCA/Vec4.h"
#include "Defs.h"

#include <OpenGL/gl.h>
#include <iostream>
#include <cmath>
#include <assert.h>

void Vec4::colourGL()
{
  glColor4fv(m_openGL);
}

Vec4::Vec4(const Vec4 &_rhs)
{
  m_x = _rhs.m_x;
  m_y = _rhs.m_y;
  m_z = _rhs.m_z;
  m_w = _rhs.m_w;
}

Vec4 Vec4::cross(const Vec4 &_r) const
{
  return Vec4(
              m_y * _r.m_z - m_z * _r.m_y,
              m_z * _r.m_x - m_x * _r.m_z,
              m_x * _r.m_y - m_y * _r.m_x,
              m_w
              );
}

float Vec4::length() const
{
  return sqrt(m_x*m_x + m_y*m_y + m_z*m_z);
}

void Vec4::normalize()
{
  float l = length();
  assert(l != 0.0f);
  m_x /= l;
  m_y /= l;
  m_z /= l;
}

void Vec4::normalGL()
{
  glNormal3f(m_x, m_y, m_z);
}

void Vec4::vertexGL()
{
  glVertex3f(m_x, m_y, m_z);
}

void Vec4::set(float _x, float _y, float _z, float _w)
{
  m_x = _x;
  m_y = _y;
  m_z = _z;
  m_w = _w;
}

float Vec4::dot(const Vec4 &_r) const
{
  return m_x * _r.m_x + m_y * _r.m_y + m_z * _r.m_z;
}

Vec4 Vec4::operator -(const Vec4 &_rhs)
{
  return Vec4(
              m_x - _rhs.m_x,
              m_y - _rhs.m_y,
              m_z - _rhs.m_z,
              m_w
              );
}

Vec4 Vec4::operator +(const Vec4 &_rhs)
{
  return Vec4(
              m_x + _rhs.m_x,
              m_y + _rhs.m_y,
              m_z + _rhs.m_z,
              m_w
              );
}

void Vec4::operator +=(const Vec4 &_rhs)
{
  m_x += _rhs.m_x;
  m_y += _rhs.m_y;
  m_z += _rhs.m_z;
}

Vec4 Vec4::operator *(float _rhs)
{
  return Vec4(
              m_x * _rhs,
              m_y * _rhs,
              m_z * _rhs,
              m_w);
}

void Vec4::operator *=(float _rhs)
{
  m_x *= _rhs;
  m_y *= _rhs;
  m_z *= _rhs;
}


Vec4 Vec4::operator /(float _rhs)
{
  return Vec4(
              m_x / _rhs,
              m_y / _rhs,
              m_z / _rhs,
              m_w);
}

/*Vec4 Vec4::sphericalCoords(float &_i, float &_j, float _offset)
{
  //  Sphere code based on a function Written by Paul Bourke.
  //  http://astronomy.swin.edu.au/~pbourke/opengl/sphere/
  // the next part of the code calculates the P,N,UV of the sphere for tri_strips

  float theta = 0.0;
  float phi = 0.0;
  Vec4 normal;
  Vec4 vertex;

  theta = (_i + 1) * TWO_PI / MOVEPRECISION - PI2;

  phi = _j * TWO_PI / MOVEPRECISION;

  normal.set(cosf(theta) * cosf(phi),sinf(theta),cosf(theta) * sinf(phi));
  vertex = normal * (WORLDRADIUS + _offset);

  return vertex;
}*/
