#ifndef PLANET_H
#define PLANET_H

#ifdef LINUX
  #include <GL/gl.h>
#endif
#ifdef DARWIN
  #include <OpenGL/gl.h>
#endif

#include <vector>

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

    model p_surface;
    model p_mountains;
    model p_waters;
    model p_waterbottoms;
    model t_leaves;
    model t_trunk;

    std::vector<Vec4> tree_positions;

    std::vector<GLuint> p_displayList;
    std::vector<GLuint> t_displayList;
};

#endif
