/*
 Copyright © 2015 Teemu Lindborg
 SDAGE 1st year 2nd PPP Assignment
*/

#include "Camera.h"
#include "NCCA/GLFunctions.h"

// ---------------------------------------------------------------------------------------
/// @file Camera.cpp
/// @brief Implementation of the camera initialisation and update functions
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------
void Camera::initCamera()
{
  // Get the MV matrix from the pos, lookat and up vectors
  this->orient = GLFunctions::orientation(m_eye,
                                          m_look,
                                          m_up);
  // Load the modelview and projection
  this->orient.loadModelView();
  GLFunctions::perspective(m_fov, m_a, m_n, m_f);
}
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------
void Camera::updateCamera()
{
  // Get the MV matrix from the pos, lookat and up vectors
  this->orient = GLFunctions::orientation(m_eye,
                                          m_look,
                                          m_up);
  // Load the modelview and projection
  this->orient.loadModelView();
  GLFunctions::perspective(m_fov, m_a, m_n, m_f);
}
// ---------------------------------------------------------------------------------------
