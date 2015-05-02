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
  this->orient = GLFunctions::orientation(eye,
                                          look,
                                          up);

  this->orient.loadModelView();
}
