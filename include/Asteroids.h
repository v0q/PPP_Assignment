/*
 Copyright © 2015 Teemu Lindborg
 SDAGE 1st year 2nd PPP Assignment
*/

#ifndef ASTEROIDS_H
#define ASTEROIDS_H

// ---------------------------------------------------------------------------------------
/// @file Asteroids.h
/// @brief Class used to define an asteroid and its attributes
/// @version 1.0
/// @author Teemu Lindborg
/// @date 03/05/15
/// Revision History:
///   -
/// @todo Tidying up, maybe figure out a way to move the asteroids when they reach the
///       surface without having to do normalisation as much.
// ---------------------------------------------------------------------------------------

#ifdef LINUX
  #include <GL/gl.h>
#endif
#ifdef DARWIN
  #include <OpenGL/gl.h>
#endif

#include <vector>

#include "Defs.h"
#include "NCCA/Vec4.h"

class Asteroid
{
  public:
    // ---------------------------------------------------------------------------------------
    /// @brief Position vector of an asteroid
    // ---------------------------------------------------------------------------------------
    Vec4 m_pos;

    // ---------------------------------------------------------------------------------------
    /// @brief Direction vector of an asteroid
    // ---------------------------------------------------------------------------------------
    Vec4 m_dir;

    // ---------------------------------------------------------------------------------------
    /// @brief Up vector of an asteroid
    // ---------------------------------------------------------------------------------------
    Vec4 m_up;

    // ---------------------------------------------------------------------------------------
    /// @brief Side vector of an asteroid
    // ---------------------------------------------------------------------------------------
    Vec4 m_side;

    // ---------------------------------------------------------------------------------------
    /// @brief Scale factor of an asteroid
    // ---------------------------------------------------------------------------------------
    float m_size;

    // ---------------------------------------------------------------------------------------
    /// @brief Speed of an asteroid
    // ---------------------------------------------------------------------------------------
    float m_speed;

    // ---------------------------------------------------------------------------------------
    /// @brief Rotation angle of an asteroid
    // ---------------------------------------------------------------------------------------
    float m_rot;

    // ---------------------------------------------------------------------------------------
    /// @brief Health of an asteroid
    // ---------------------------------------------------------------------------------------
    int m_life;

    // ---------------------------------------------------------------------------------------
    /// @brief 3d model
    // ---------------------------------------------------------------------------------------
    int c_aType;

    // ---------------------------------------------------------------------------------------
    /// @brief Default constructor for an asteroid
    /// @param[in] _p Position vector
    /// @param[in] _d Direction vector
    /// @param[in] _up Up vector
    /// @param[in] _side Side vector
    /// @param[in] _s Scale factor
    /// @param[in] _sp Speed value
    /// @param[in] _l Life/health
    /// @param[in] _t Asteroid type for different models
    // ---------------------------------------------------------------------------------------
    Asteroid(
             const Vec4 &_p,
             const Vec4 &_d,
             const Vec4 &_up,
             const Vec4 &_side,
             const float _s,
             const float _sp,
             const float _l,
             const int _t
            ) :
             m_pos(_p),
             m_dir(_d),
             m_up(_up),
             m_side(_side),
             m_size(_s),
             m_speed(_sp),
             m_rot(0.0),
             m_life(_l),
             c_aType(_t) {;}

    // ---------------------------------------------------------------------------------------
    /// @brief Default destructor
    // ---------------------------------------------------------------------------------------
    ~Asteroid() {}

    // ---------------------------------------------------------------------------------------
    /// @brief Function that will call the correct displaylist, scale, rotate and translate
    ///        the asteroid to its correct position
    /// @param[in] _dL displaylist holding both asteroid models
    // ---------------------------------------------------------------------------------------
    void draw(
              const std::vector<GLuint> &_dL
             );

    // ---------------------------------------------------------------------------------------
    /// @brief Handles the movement of an asteroid
    // ---------------------------------------------------------------------------------------
    void move();
}; // end of class

#endif // end of ASTEROIDS_H
