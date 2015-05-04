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
    /// @param[in] _eye Eye position vector of the camera
    /// @param[in] _look Look at vector
    /// @param[in] _up Up vector of the camera
    /// @return The modelview/look at matrix
    // -----------------------------------------------------------------------------------------
    static Mat4 orientation(
                            const Vec4 &_eye,
                            const Vec4 &_look,
                            const Vec4 &_up
                           );

    // ---------------------------------------------------------------------------------------
    /// @brief Generates a projection matrix and loads it.
    /// @param[in] _fovy Field of view angle
    /// @param[in] _aspect Aspect ratio
    /// @param[in] _zNear Near clipping plane
    /// @param[in] _zFar Far clipping plane
    // ---------------------------------------------------------------------------------------
    static void perspective(
                            const float _fovy,
                            const float _aspect,
                            const float _zNear,
                            const float _zFar
                           );

    // ---------------------------------------------------------------------------------------
    /// @brief Converts degrees into radians.
    /// @param[in] _deg Degree to convert
    /// @return Radian value
    // ---------------------------------------------------------------------------------------
    static float radians(
                         const float _deg
                        );

  protected:
    // ---------------------------------------------------------------------------------------
    /// @brief Default ctor
    // ---------------------------------------------------------------------------------------
    GLFunctions();

    // ---------------------------------------------------------------------------------------
    /// @brief Default copy ctor
    // ---------------------------------------------------------------------------------------
    GLFunctions(
                const GLFunctions &
               );

    // ---------------------------------------------------------------------------------------
    /// @brief Default dtor
    // ---------------------------------------------------------------------------------------
    ~GLFunctions();
}; // end of class

#endif // end GLFUNCTIONS_H
