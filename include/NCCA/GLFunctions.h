/*
 Copyright © 2015 Teemu Lindborg
 SDAGE 1st year 2nd PPP Assignment
 Initial code © by Jonathan Macey
*/

#ifndef GLFUNCTIONS_H
#define GLFUNCTIONS_H

// ---------------------------------------------------------------------------------------
/// @file GLFunctions.h
/// @brief Object holding the functions for ModelView and Perspective matrix calculations
/// @version 1.0
/// @author Jonathan Macey, minor modifications made by Teemu Lindborg
/// @date 03/05/15
/// Revision History:
///   -
/// @todo Maybe not necessary to have this stuff as an object but just have
///       'em in a namespace
// ---------------------------------------------------------------------------------------

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
  public:
    // ---------------------------------------------------------------------------------------
    /// @brief Calculates the modelview/look at matrix, used to orient the player as well.
    /// @param _eye Eye position vector of the camera
    /// @param _look Look at vector
    /// @param _up Up vector of the camera
    /// @return The modelview/look at matrix
    // -----------------------------------------------------------------------------------------
    static Mat4 orientation(Vec4 _eye, Vec4 _look, const Vec4 _up);

    // ---------------------------------------------------------------------------------------
    /// @brief Generates a projection matrix and loads it.
    /// @param _fovy Field of view angle
    /// @param _aspect Aspect ratio
    /// @param _zNear Near clipping plane
    /// @param _zFar Far clipping plane
    // ---------------------------------------------------------------------------------------
    static void perspective(const float _fovy, const float _aspect, const float _zNear, const float _zFar);

    // ---------------------------------------------------------------------------------------
    /// @brief Converts degrees into radians.
    /// @param _deg Degree to convert
    /// @return Radian value
    // ---------------------------------------------------------------------------------------
    static float radians(const float _deg );

  protected:
    // ---------------------------------------------------------------------------------------
    /// @brief Default ctor
    // ---------------------------------------------------------------------------------------
    GLFunctions();

    // ---------------------------------------------------------------------------------------
    /// @brief Default copy ctor
    // ---------------------------------------------------------------------------------------
    GLFunctions(const GLFunctions &);

    // ---------------------------------------------------------------------------------------
    /// @brief Default dtor
    // ---------------------------------------------------------------------------------------
    ~GLFunctions();
}; // end of class

#endif // end GLFUNCTIONS_H
