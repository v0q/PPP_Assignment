#include "Camera.h"
#include "NCCA/GLFunctions.h"

void Camera::initCamera()
{
  this->orient = GLFunctions::orientation(eye,
                                          look,
                                          up);
  this->orient.loadModelView();
  GLFunctions::perspective(fov, a, n, f);
}

void Camera::updateCamera()
{
  glLoadIdentity();

  this->orient = GLFunctions::orientation(eye,
                                          look,
                                          up);

  this->orient.loadModelView();

  /*Vec4 lPos = eye;
  lPos.normalize();
  GLfloat light_position[] = {lPos.m_x, lPos.m_y, lPos.m_z , 0.0 };
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);*/
}
