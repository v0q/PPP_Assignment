/*
 Copyright © 2015 Teemu Lindborg
 SDAGE 1st year 2nd PPP Assignment
 Initial code © by Jon Macey
*/

#include <cmath>

#include "NCCA/Vec4.h"
#include "NCCA/GLFunctions.h"

// ---------------------------------------------------------------------------------------
/// @file GLFunctions.cpp
/// @brief Implementation for GLFunctions class
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------
Mat4 GLFunctions::orientation(
                              const Vec4 &_eye,
                              const Vec4 &_look,
                              const Vec4 &_up
                             )
{
  Vec4 n = _look-_eye;
  Vec4 u = _up;
  Vec4 v = n.cross(u);
  u = v.cross(n);
  n.normalize();
  v.normalize();
  u.normalize();

  Mat4 mv(1.0f);
  mv.m_00 = v.m_x;
  mv.m_10 = v.m_y;
  mv.m_20 = v.m_z;
  mv.m_01 = u.m_x;
  mv.m_11 = u.m_y;
  mv.m_21 = u.m_z;
  mv.m_02 = -n.m_x;
  mv.m_12 = -n.m_y;
  mv.m_22 = -n.m_z;
  mv.m_30 = -_eye.dot(v);
  mv.m_31 = -_eye.dot(u);
  mv.m_32 = _eye.dot(n);

  return mv;
}
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------
void GLFunctions::perspective(
                              const float _fovy,
                              const float _aspect,
                              const float _zNear,
                              const float _zFar
                             )
{
  float range = tan(radians(_fovy / 2.0)) * _zNear;
  float left = -range * _aspect;
  float right = range * _aspect;
  float bottom = -range;
  float top = range;
  Mat4 result;
  result.m_00 = (2.0f * _zNear) / (right - left);
  result.m_11 = (2.0f * _zNear) / (top - bottom);
  result.m_22 = - (_zFar + _zNear) / (_zFar - _zNear);
  result.m_23 = - 1.0f;
  result.m_32 = - (2.0f* _zFar * _zNear) / (_zFar - _zNear);
  result.loadProjection();
}
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------
float GLFunctions::radians(
                           const float _deg
                          )
{
  return (_deg/180.0f) * M_PI;
}
// ---------------------------------------------------------------------------------------
