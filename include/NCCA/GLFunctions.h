#ifndef GLFUNCTIONS_H__
#define GLFUNCTIONS_H__

#include <OpenGL/gl.h>

#include "Vec4.h"
#include <cmath>

class GLFunctions
{
  public :
    static void lookAt(Vec4 _eye, Vec4 _look, Vec4 _up);
    static void perspective(float _fovy,float _aspect, float _zNear, float _zFar);
    static float radians(float _deg );
  private :
    GLFunctions();
    ~GLFunctions();
    GLFunctions(const GLFunctions &);

};

#endif
