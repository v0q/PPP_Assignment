#ifndef PLANET_H
#define PLANET_H

#ifdef LINUX
  #include <GL/gl.h>
#endif
#ifdef DARWIN
  #include <OpenGL/gl.h>
#endif

#include <vector>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>

#include "LoadOBJ.h"
#include "NCCA/Vec4.h"

class Planet
{
  public:
    Planet();
    ~Planet();
    void draw();

  private:
    void genSurface();
    void genMountains();
    void genWaters();
    void genWaterbottoms();
    void genTree();
    void genClouds();

    typedef struct
    {
      Vec4 rAxis;
      float rot;
      float scale;
    } cloud;

    int max_clouds;

    model p_surface;
    model p_mountains;
    model p_waters;
    model p_waterbottoms;
    model t_leaves;
    model t_trunk;
    model m_cloud;

    std::vector<Vec4> tree_positions;
    std::vector<cloud> clouds;

    std::vector<GLuint> p_displayList;
    std::vector<GLuint> c_displayList;
    std::vector<GLuint> t_displayList;

    GLuint c_texture;

    boost::mt19937 rng;
};

#endif
