/*
 Copyright © 2015 Teemu Lindborg
 SDAGE 1st year 2nd PPP Assignment
*/

#ifndef CAMERA_H
#define CAMERA_H

// ---------------------------------------------------------------------------------------
/// @file Camera.h
/// @brief Class to handle camera and its movement
/// @version 1.0
/// @author Teemu Lindborg
/// @date 03/05/15
/// Revision History:
///   -
/// @todo Understand the GL pipeline properly and load/use projection and modelview
///       matrices properly, thus possibly update the updateCamera() function
// ---------------------------------------------------------------------------------------

#include "Defs.h"
#include "NCCA/Vec4.h"
#define CAMRADIUS 6.0f

class Camera
{
  public:
    // ---------------------------------------------------------------------------------------
    /// @brief Vector holding the camera position
    // ---------------------------------------------------------------------------------------
    Vec4 m_eye;

    // ---------------------------------------------------------------------------------------
    /// @brief Vector holding the position to look at
    // ---------------------------------------------------------------------------------------
    Vec4 m_look;

    // ---------------------------------------------------------------------------------------
    /// @brief Up vector of the camera
    // ---------------------------------------------------------------------------------------
    Vec4 m_up;

    // ---------------------------------------------------------------------------------------
    /// @brief Side vector of the camera
    // ---------------------------------------------------------------------------------------
    Vec4 m_w;

    // ---------------------------------------------------------------------------------------
    /// @brief Field of view angle
    // ---------------------------------------------------------------------------------------
    float m_fov;

    // ---------------------------------------------------------------------------------------
    /// @brief Near and far clipping plane distances
    // ---------------------------------------------------------------------------------------
    float m_n, m_f;

    // ---------------------------------------------------------------------------------------
    /// @brief Aspect ratio
    // ---------------------------------------------------------------------------------------
    float m_a;

    Mat4 orient;

    Camera(): m_eye(0.0f, 0.0f, CAMRADIUS),
              m_look(0.0f, 0.0f, 0.0f),
              m_up(0.0f, 1.0f, 0.0f),
              m_fov(65.0f),
              m_n(0.5f),
              m_f(200.0f),
              m_a(SCREENWIDTH / (float)SCREENHEIGHT)
    { }
    ~Camera() { }

    // ---------------------------------------------------------------------------------------
    /// @brief Initialises the camera by loading the projection and modelview matrices
    // ---------------------------------------------------------------------------------------
    void initCamera();

    // ---------------------------------------------------------------------------------------
    /// @brief Updates the camera based on the new position, look and up vectors
    // ---------------------------------------------------------------------------------------
    void updateCamera();

}; // end of class

#endif // end of CAMERA_H
