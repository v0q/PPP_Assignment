#ifndef VEC4_H__
#define VEC4_H__

#include <string>
#include "Mat4.h"

class Vec4
{
  public:
    // Copy constructor, takes a copy of "itself"
    Vec4(const Vec4 &_rhs);
    Vec4(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f, float _w = 1.0f) :
      m_x(_x), m_y(_y), m_z(_z), m_w(_w){}

    // Use the current vec4 as a call to glColor4fv()
    void colourGL();
    // Return the cross product of this vector with r
    Vec4 cross(const Vec4 &_r) const;
    // Calculate the dot product of this vector with _r
    float dot(const Vec4 &_r) const;
    // Calculate the length of the vector
    float length() const;
    // Calculate the length squared
    float lengthSquared() const;
    // Set the current Vec4 as the call to glNormal3fv(x,y,z)
    void normalGL();
    // Set the current Vec4 as the call to glNormal3fv(-x,-y,-z)
    void normalInvGL();
    // Set the current Vec4 as the call to glTexCoord2f(x, y);
    void textureGL();
    // Call glVertex3f with components
    void vertexGL();
    // Normalize this vector
    void normalize();

    // Operator overload, we can build in our own calculation stuff
    // Usage: V1 * Mat4
    Vec4 operator *(const Mat4 &_rhs);
    // * a scalar
    Vec4 operator *(float _rhs);
    // / a scalar
    Vec4 operator /(float _rhs);
    // V1 *= 2
    void operator *=(float _rhs);
    // V1 + V2
    Vec4 operator +(const Vec4 &_rhs);
    // V1 += V2
    void operator +=(const Vec4 &_rhs);
    // V1 - V2
    Vec4 operator -(const Vec4 &_rhs);
    // V1 -= V2
    void operator -=(const Vec4 &_rhs);
    // Equality V1 == V2 (bool)
    bool operator ==(const Vec4 &_rhs);
    // subscript operator Vec4 v; v[0]==1.0; => set x
    float & operator [](int _i);
    // Set components
    void set(float _x, float _y, float _z, float _w = 1.0f);


    //static Vec4 sphericalCoords(float &_i, float &_j, float _offset);

    union
    {
      struct
      {
        float m_x;
        float m_y;
        float m_z;
        float m_w;
      };
      float m_openGL[4];
    };


  private:

};

#endif
