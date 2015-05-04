/*
 Copyright © 2015 Teemu Lindborg
 SDAGE 1st year 2nd PPP Assignment
*/

#ifndef PARTICLES_H
#define PARTICLES_H

// ---------------------------------------------------------------------------------------
/// @file Particles.h
/// @brief Class for a simple particle
/// @version 1.0
/// @author Teemu Lindborg
/// @date 03/05/15
/// Revision History:
///   -
/// @todo Make the "sprouting" of better
// ---------------------------------------------------------------------------------------

#ifdef LINUX
  #include <GL/gl.h>
#endif
#ifdef DARWIN
  #include <OpenGL/gl.h>
#endif

#include <iostream>

#include "NCCA/Vec4.h"

class Particle
{
  public:

    // ---------------------------------------------------------------------------------------
    /// @brief Holds the elapsed life of a particle
    // ---------------------------------------------------------------------------------------
    int m_life;

    // ---------------------------------------------------------------------------------------
    /// @brief Holds the maximum lifetime of a particle
    // ---------------------------------------------------------------------------------------
    int m_max_life;

    // ---------------------------------------------------------------------------------------
    /// @brief Default ctor for a particle
    /// @param[in] _p Vector for initial position of the particle
    /// @param[in] _l Maximum lifetime of the given particle
    // ---------------------------------------------------------------------------------------
    Particle(
             const Vec4 &_p,
             const int _l = 0
            ) :
             m_life(0),
             m_max_life(_l),
             m_pos(_p)
            {
              // Generate random values on how much the particle moves each frame in which axis
              m_moveX = 0.01 * (std::rand()/(float)RAND_MAX * 2 - 1);
              m_moveY = 0.01 * (std::rand()/(float)RAND_MAX * 2 - 1);
              m_moveZ = 0.01 * (std::rand()/(float)RAND_MAX * 2 - 1);
            }

    // ---------------------------------------------------------------------------------------
    /// @brief Default dtor
    // ---------------------------------------------------------------------------------------
    ~Particle() {}

    // ---------------------------------------------------------------------------------------
    /// @brief Draws and calculates the color of the particle based on elapsed life
    ///        relative to its maximum lifetime
    // ---------------------------------------------------------------------------------------
    void draw();

    // ---------------------------------------------------------------------------------------
    /// @brief Moves the particle after it's born
    // ---------------------------------------------------------------------------------------
    void move();

  protected:
    // ---------------------------------------------------------------------------------------
    /// @brief Variables holding the movement amount on each axis for a particle
    // ---------------------------------------------------------------------------------------
    float m_moveX, m_moveY, m_moveZ;

    // ---------------------------------------------------------------------------------------
    /// @brief The actual position vector of a particle
    // ---------------------------------------------------------------------------------------
    Vec4 m_pos;
}; // end of class

#endif // end of PARTICLES_H
