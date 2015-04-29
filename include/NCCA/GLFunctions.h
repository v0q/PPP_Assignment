#ifndef GLFUNCTIONS_H__
#define GLFUNCTIONS_H__

#ifdef LINUX
  #include <GL/gl.h>
#endif
#ifdef DARWIN
  #include <OpenGL/gl.h>
#endif

#include <cmath>

#include "Vec4.h"

class GLFunctions
{
  public :
    static Mat4 orientation(Vec4 _eye, Vec4 _look, Vec4 _up);
    static void perspective(float _fovy,float _aspect, float _zNear, float _zFar);
    static float radians(float _deg );
  private :
    GLFunctions();
    ~GLFunctions();
    GLFunctions(const GLFunctions &);

};

#endif
