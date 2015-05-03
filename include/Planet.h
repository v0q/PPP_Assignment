/*
 Copyright © 2015 Teemu Lindborg
 SDAGE 1st year 2nd PPP Assignment
*/

#ifndef PLANET_H
#define PLANET_H

// ---------------------------------------------------------------------------------------
/// @file Planet.h
/// @brief Class used to build the planet and generate trees and clouds on its surface
/// @version 1.0
/// @author Teemu Lindborg
/// @date 03/05/15
/// Revision History:
///   -
/// @todo Fine tune the height based vertex coloring on the surface. Also figure out
///       how to have the transparent water accumulate the color of the waterbottoms
///       beneath it to give it more depth.
// ---------------------------------------------------------------------------------------

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
    // ---------------------------------------------------------------------------------------
    /// @brief Default ctor for the planet. Loads the models and calls the generator functions
    // ---------------------------------------------------------------------------------------
    Planet();

    // ---------------------------------------------------------------------------------------
    /// @brief Default dtor. Frees the memory used by the models etc.
    // ---------------------------------------------------------------------------------------
    ~Planet();

    // ---------------------------------------------------------------------------------------
    /// @brief Calls the correct displaylists, translates, performs rotations and scaling and
    ///        draws all the planet elements.
    // ---------------------------------------------------------------------------------------
    void draw();

  protected:
    // ---------------------------------------------------------------------------------------
    /// @brief Maximum amount of clouds we can have on the scene, this is randomised.
    // ---------------------------------------------------------------------------------------
    int max_clouds;

    // ---------------------------------------------------------------------------------------
    /// @brief Model structure used to store the planet surface data
    // ---------------------------------------------------------------------------------------
    model m_pSurface;

    // ---------------------------------------------------------------------------------------
    /// @brief Model structure used to store the mountain data
    // ---------------------------------------------------------------------------------------
    model m_pMountains;

    // ---------------------------------------------------------------------------------------
    /// @brief Model structure used to store the water surface data
    // ---------------------------------------------------------------------------------------
    model m_pWaters;

    // ---------------------------------------------------------------------------------------
    /// @brief Model structure used to store the seabed data
    // ---------------------------------------------------------------------------------------
    model m_pSeabeds;

    // ---------------------------------------------------------------------------------------
    /// @brief Model structure used to store the tree leaf data
    // ---------------------------------------------------------------------------------------
    model m_tLeaves;

    // ---------------------------------------------------------------------------------------
    /// @brief Model structure used to store the tree trunk data
    // ---------------------------------------------------------------------------------------
    model m_tTrunk;

    // ---------------------------------------------------------------------------------------
    /// @brief Model structure used to store the cloud data
    // ---------------------------------------------------------------------------------------
    model m_cloudGeometry;

    typedef struct
    {
      // ---------------------------------------------------------------------------------------
      /// @brief Vector for the rotation axis of a cloud
      // ---------------------------------------------------------------------------------------
      Vec4 m_rAxis;

      // ---------------------------------------------------------------------------------------
      /// @brief Rotation angle of a cloud
      // ---------------------------------------------------------------------------------------
      float m_rot;

      // ---------------------------------------------------------------------------------------
      /// @brief Scale factor of a cloud
      // ---------------------------------------------------------------------------------------
      float m_scale;
    } m_cloud;

    // ---------------------------------------------------------------------------------------
    /// @brief stl vector used to store the location of each tree
    // ---------------------------------------------------------------------------------------
    std::vector<Vec4> tree_positions;

    // ---------------------------------------------------------------------------------------
    /// @brief stl vector used to store the cloud data
    // ---------------------------------------------------------------------------------------
    std::vector<m_cloud> clouds;

    // ---------------------------------------------------------------------------------------
    /// @brief stl vector holding the displaylists for the planet's elements
    // ---------------------------------------------------------------------------------------
    std::vector<GLuint> p_displayList;

    // ---------------------------------------------------------------------------------------
    /// @brief stl vector holding the displaylists for the clouds
    // ---------------------------------------------------------------------------------------
    std::vector<GLuint> c_displayList;

    // ---------------------------------------------------------------------------------------
    /// @brief stl vector holding the displaylists for the trees
    // ---------------------------------------------------------------------------------------
    std::vector<GLuint> t_displayList;

    // ---------------------------------------------------------------------------------------
    /// @brief Boost random number generator
    // ---------------------------------------------------------------------------------------
    boost::mt19937 rng;

    // ---------------------------------------------------------------------------------------
    /// @brief Loads the the planet's surface to a displaylist and adjusts the vertex colors
    ///        based on the distance/"height" of the vertex
    // ---------------------------------------------------------------------------------------
    void genSurface();

    // ---------------------------------------------------------------------------------------
    /// @brief Loads the planet's mountains to a displaylist and does some minor height
    ///        based coloring
    // ---------------------------------------------------------------------------------------
    void genMountains();

    // ---------------------------------------------------------------------------------------
    /// @brief Loads the water surfaces to a displaylist and sets 'em to be a bit transparent
    // ---------------------------------------------------------------------------------------
    void genWaters();

    // ---------------------------------------------------------------------------------------
    /// @brief Loads the seabeds to a displaylist and does minor height based coloring
    // ---------------------------------------------------------------------------------------
    void genSeabeds();

    // ---------------------------------------------------------------------------------------
    /// @brief Loads the tree leaves and trunk data to a displaylist
    // ---------------------------------------------------------------------------------------
    void genTree();

    // ---------------------------------------------------------------------------------------
    /// @brief Loads the cloud model(s) to a displaylist and generates the positions and
    ///        random rotation axes for each cloud
    // ---------------------------------------------------------------------------------------
    void genClouds();
}; // end of class

#endif // end of PLANET_H
