/*
 Copyright © 2015 Teemu Lindborg
 SDAGE 1st year 2nd PPP Assignment
*/

#ifndef PROJECTILE_H
#define PROJECTILE_H

// ---------------------------------------------------------------------------------------
/// @file Projectile.h
/// @brief Class for a projectile, holding it's attributes and movement and drawing
///        functionality
/// @version 1.0
/// @author Teemu Lindborg
/// @date 03/05/15
/// Revision History:
///   -
/// @todo Tidying up. Changing the projectiles so that they would look like more of a
///       stream of particles (slow moving laser sort of effect)
// ---------------------------------------------------------------------------------------

#include <vector>

#include "LoadOBJ.h"
#include "Particles.h"
#include "NCCA/Vec4.h"

// Set the projectile movement speed
#define PROJECTILESPEED 0.1

class Projectile
{
  public:
    // ---------------------------------------------------------------------------------------
    /// @brief Position vector of a projectile
    // ---------------------------------------------------------------------------------------
    Vec4 m_pos;

    // ---------------------------------------------------------------------------------------
    /// @brief Up vector of a projectile
    // ---------------------------------------------------------------------------------------
    Vec4 m_up;

    // ---------------------------------------------------------------------------------------
    /// @brief Left vector of a projectile
    // ---------------------------------------------------------------------------------------
    Vec4 m_left;

    // ---------------------------------------------------------------------------------------
    /// @brief Normal vector of a projectile
    // ---------------------------------------------------------------------------------------
    Vec4 m_normal;

    // ---------------------------------------------------------------------------------------
    /// @brief Direction to move the projectiles to (radians)
    // ---------------------------------------------------------------------------------------
    float m_dir;

    // ---------------------------------------------------------------------------------------
    /// @brief Elapsed life of a particle
    // ---------------------------------------------------------------------------------------
    int m_life;

    // ---------------------------------------------------------------------------------------
    /// @brief Maximum life of a particle
    // ---------------------------------------------------------------------------------------
    int m_maxLife;

    // ---------------------------------------------------------------------------------------
    /// @brief Constructor for a projectile, initialises all the attributes
    /// @param[in] _px Position x value
    /// @param[in] _py Position y value
    /// @param[in] _pz Position z value
    /// @param[in] _u Up vector of the projectile, used for moving the projectile around the
    ///           atmosphere
    /// @param[in] _l Left vector of the projectile, used for moving the projectile around the
    ///           atmosphere
    /// @param[in] _nx X component of the normal vector
    /// @param[in] _ny Y component of the normal vector
    /// @param[in] _nz Z component of the normal vector
    /// @param[in] _d Direction angle in radians
    /// @param[in] _ml Maximum life of the projectile
    // ---------------------------------------------------------------------------------------
    Projectile(
               const float &_px,
               const float &_py,
               const float &_pz,
               const Vec4 &_u,
               const Vec4 &_l,
               const float &_nx,
               const float &_ny,
               const float &_nz,
               const float &_d,
               const float &_ml
              ) :
               m_pos(_px, _py, _pz),
               m_up(_u),
               m_left(_l),
               m_normal(_nx, _ny, _nz),
               m_dir(_d),
               m_life(0),
               m_maxLife(_ml) {;}

    // ---------------------------------------------------------------------------------------
    /// @brief Default dtor
    // ---------------------------------------------------------------------------------------
    ~Projectile() {}

    // ---------------------------------------------------------------------------------------
    /// @brief Function that moves, animates the sprite and draws a projectile
    /// @param[in] _itAmt Amount of iterations to for a projectile to have it move "smoothly"
    ///                   move between two points rather than skipping certain positions
    /// @param[in] _cu Up vector of the camera, used to bilboard the projectile
    /// @param[in] _cl Up vector of the camera, used to bilboard the projectile
    // ---------------------------------------------------------------------------------------
    void drawProjectile(
                        const int _itAmt,
                        const Vec4 &_cu,
                        const Vec4 &_cl
                       );
}; // end of class

#endif // end of PROJECTILE_H
