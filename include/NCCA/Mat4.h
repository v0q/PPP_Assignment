#ifndef MAT4_H__
#define MAT4_H__

class Mat4
{
  public:

    // Construct Mat4 as scale matrix _s
    Mat4(float _s=1.0f);
    // Copy constructor
    Mat4(const Mat4 &_rhs);

    // * operator
    void operator *=(const Mat4 &_rhs);
    Mat4 operator *(double _rhs);

    void normalize();

    // Set to identity
    void identity();
    // Load gl model view
    void loadModelView() const;
    // Load gl projection
    void loadProjection() const;

    union
    {
      float m_m[4][4];
      float m_openGL[16];
      struct
      {
        float m_00;
        float m_01;
        float m_02;
        float m_03;
        float m_10;
        float m_11;
        float m_12;
        float m_13;
        float m_20;
        float m_21;
        float m_22;
        float m_23;
        float m_30;
        float m_31;
        float m_32;
        float m_33;
      };
    };

  private:

};

#endif
