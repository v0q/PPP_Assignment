/*
 Copyright © 2015 Teemu Lindborg
 SDAGE 1st year 2nd PPP Assignment
 Initial code © by Jonathan Macey
*/

#ifndef VEC4_H
#define VEC4_H

// ---------------------------------------------------------------------------------------
/// @file Vec4.h
/// @brief Simple Vector class
/// @version 1.0
/// @author Jonathan Macey, minor modifications made by Teemu Lindborg
/// @date 03/05/15
/// Revision History:
///   -
/// @todo Implement all the functions that have not yet been implemented
// ---------------------------------------------------------------------------------------

#include <string>
#include "Mat4.h"

class Vec4
{
  public:
    // ---------------------------------------------------------------------------------------
    /// @brief Copy ctor that makes a copy of the rhs vector
    /// @param[in] _rhs Vector to be copied
    // ---------------------------------------------------------------------------------------
    Vec4(
         const Vec4 &_rhs
        );

    // ---------------------------------------------------------------------------------------
    /// @brief Construct a 4d vector
    /// @param[in] _x Point/value x
    /// @param[in] _y Point/value y
    /// @param[in] _z Point/value z
    /// @param[in] _w Point/value w
    // ---------------------------------------------------------------------------------------
    Vec4(
         const float _x = 0.0f,
         const float _y = 0.0f,
         const float _z = 0.0f,
         const float _w = 1.0f
        ) :
         m_x(_x),
         m_y(_y),
         m_z(_z),
         m_w(_w) {;}

    // ---------------------------------------------------------------------------------------
    /// @brief Calls the current Vector as glColor4fv();
    // ---------------------------------------------------------------------------------------
    void colourGL() const;

    // ---------------------------------------------------------------------------------------
    /// @brief Calculates the cross product between two vectors
    /// @param[in] _rhs Rhs of v1 cross v2
    /// @return Return the cross product of this vector with rhs
    // ---------------------------------------------------------------------------------------
    Vec4 cross(
               const Vec4 &_rhs
              ) const;

    // ---------------------------------------------------------------------------------------
    /// @brief Calculate the dot product of two vectors
    /// @param[in] _rhs Rhs of v1 dot v2
    /// @return Dot product of the two vectors
    // ---------------------------------------------------------------------------------------
    float dot(
              const Vec4 &_rhs
             ) const;

    // ---------------------------------------------------------------------------------------
    /// @brief Calculates the length of the vector
    /// @return The length value
    // ---------------------------------------------------------------------------------------
    float length() const;

    // ---------------------------------------------------------------------------------------
    /// @brief Calculate the length squared of the vector
    /// @return The length squared
    // ---------------------------------------------------------------------------------------
    float lengthSquared() const;

    // ---------------------------------------------------------------------------------------
    /// @brief Calls the current vector as glNormal3f(m_x, m_y, m_z)
    // ---------------------------------------------------------------------------------------
    void normalGL() const;

    // ---------------------------------------------------------------------------------------
    /// @brief Calls the current vector as glNormal3f(-m_x, -m_y, -m_z)
    // ---------------------------------------------------------------------------------------
    void normalInvGL() const;

    // ---------------------------------------------------------------------------------------
    /// @brief Calls the current vector as glTexCoord2f(m_x, m_y)
    // ---------------------------------------------------------------------------------------
    void textureGL() const;

    // ---------------------------------------------------------------------------------------
    /// @brief Calls the current vector as glVertex3f(m_x, m_y, m_z)
    // ---------------------------------------------------------------------------------------
    void vertexGL() const;

    // ---------------------------------------------------------------------------------------
    /// @brief Normalizes the vector
    // ---------------------------------------------------------------------------------------
    void normalize();

    // ---------------------------------------------------------------------------------------
    /// @brief * operator multiplies a vector by a matrix V * M
    /// @param[in] _rhs Matrix to multiply the vector with
    /// @return Resulting vector
    // ---------------------------------------------------------------------------------------
    Vec4 operator *(
                    const Mat4 &_rhs
                   ) const;

    // ---------------------------------------------------------------------------------------
    /// @brief * operator to multiply a vector by a scalar V1 * _rhs
    /// @param[in] _rhs Scalar value to multiply with
    /// @return The resulting vector
    // ---------------------------------------------------------------------------------------
    Vec4 operator *(
                    const float _rhs
                   ) const;

    // ---------------------------------------------------------------------------------------
    /// @brief / operator to divide the vector by a scalar. V1 / _rhs
    /// @param[in] _rhs Scalar value to divide with
    /// @return The resulting vector
    // ---------------------------------------------------------------------------------------
    Vec4 operator /(
                    const float _rhs
                   ) const;

    // ---------------------------------------------------------------------------------------
    /// @brief *= operator to multiply the current vector by a scalar. V *= _rhs
    /// @param[in] _rhs Scalar value to multiply the vector with
    // ---------------------------------------------------------------------------------------
    void operator *=(
                     const float _rhs
                    );

    // ---------------------------------------------------------------------------------------
    /// @brief + operator to do vector addition. Adds to vectors together. V1 + V2
    /// @param[in] _rhs Rhs of the operation
    /// @return The resulting vector
    // ---------------------------------------------------------------------------------------
    Vec4 operator +(
                    const Vec4 &_rhs
                   ) const;

    // ---------------------------------------------------------------------------------------
    /// @brief += operator to add V2 to the current vector V1 += V2
    /// @param[in] _rhs Vector to be added
    // ---------------------------------------------------------------------------------------
    void operator +=(
                     const Vec4 &_rhs
                    );

    // ---------------------------------------------------------------------------------------
    /// @brief - operator for vector substraction. V1 - V2
    /// @param[in] _rhs Rhs of the substraction
    /// @return The resulting vector
    // ---------------------------------------------------------------------------------------
    Vec4 operator -(
                    const Vec4 &_rhs
                   ) const;

    // ---------------------------------------------------------------------------------------
    /// @brief -= operator to substract V2 from the current vector V1 -= V2
    /// @param[in] _rhs Vector to be used for the substraction
    // ---------------------------------------------------------------------------------------
    void operator -=(
                     const Vec4 &_rhs
                    );

    // ---------------------------------------------------------------------------------------
    /// @brief == operator to check if two vectors are the same V1 == V2
    /// @param[in] _rhs Vector to compare the first one with
    /// @return True if two vectors are the same, false if not
    // ---------------------------------------------------------------------------------------
    bool operator ==(
                     const Vec4 &_rhs
                    );

    // ---------------------------------------------------------------------------------------
    /// @brief subscript operator Vec4 v; v[0]==1.0; => set x
    /// @param[in] _i Index to access
    /// @return The value at given index
    // ---------------------------------------------------------------------------------------
    float & operator [](
                        const int _i
                       );

    // ---------------------------------------------------------------------------------------
    /// @brief Set values to the vector
    /// @param[in] _x Point/value x
    /// @param[in] _y Point/value y
    /// @param[in] _z Point/value z
    /// @param[in] _w Point/value w
    // ---------------------------------------------------------------------------------------
    void set(
             const float _x,
             const float _y,
             const float _z,
             const float _w = 1.0f
            );

    union
    {
      // ---------------------------------------------------------------------------------------
      /// @brief Vector element, mapped to m_openGL[4] by union, useful for GL fv formats
      // ---------------------------------------------------------------------------------------
      float m_openGL[4];
      struct
      {
        // ---------------------------------------------------------------------------------------
        /// @brief Vector x-element, maps to m_openGL[0]
        // ---------------------------------------------------------------------------------------
        float m_x;

        // ---------------------------------------------------------------------------------------
        /// @brief Vector y-element, maps to m_openGL[1]
        // ---------------------------------------------------------------------------------------
        float m_y;

        // ---------------------------------------------------------------------------------------
        /// @brief Vector z-element, maps to m_openGL[2]
        // ---------------------------------------------------------------------------------------
        float m_z;

        // ---------------------------------------------------------------------------------------
        /// @brief Vector z-element, maps to m_openGL[3]
        // ---------------------------------------------------------------------------------------
        float m_w;
      }; // end of struct
    }; // end of union

}; // end of class

#endif // end of VEC4_H
