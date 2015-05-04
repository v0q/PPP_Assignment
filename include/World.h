/*
 Copyright © 2015 Teemu Lindborg
 SDAGE 1st year 2nd PPP Assignment
*/

#ifndef WORLD_H
#define WORLD_H

#ifdef LINUX
  #include <GL/gl.h>
#endif
#ifdef DARWIN
  #include <OpenGL/gl.h>
#endif

#include <vector>
#include <list>
#include <string>
#include <cmath>
#include <SDL2/SDL_mixer.h>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>

#include "Asteroids.h"
#include "Planet.h"
#include "LoadOBJ.h"
#include "NCCA/Vec4.h"

// ---------------------------------------------------------------------------------------
/// @file World.h
/// @brief Class that handles the building of the world, stars, asteroids, triangle
///        subdivision, asteroid spatial partitioning, loading and playing of the
///        background music.
/// @version 1.0
/// @author Teemu Lindborg
/// @date 03/05/15
/// Revision History:
///   -
/// @todo Tidying up. Some functionality could be separated in to their own classes.
// ---------------------------------------------------------------------------------------

// Skybox scale factor
#define SKYBOXRADIUS 15

class World
{
  public:
    // ---------------------------------------------------------------------------------------
    /// @brief stl vector holding the living asteroids
    // ---------------------------------------------------------------------------------------
    std::vector<Asteroid> m_asteroids;

    // ---------------------------------------------------------------------------------------
    /// @brief stl list holding the indices of living asteroids that have reached the
    ///        atmosphere. Used for collision detection.
    // ---------------------------------------------------------------------------------------
    std::list<int> m_aColIndices;

    // ---------------------------------------------------------------------------------------
    /// @brief Variable telling how many asteroids can be alive at the same time, if this
    ///        value is reached no more asteroids are generated before old ones are destroyed
    // ---------------------------------------------------------------------------------------
    int m_maxAsteroids;

    // ---------------------------------------------------------------------------------------
    /// @brief World constructor initialises and calls the building functions that are needed
    ///        to draw/generate the world. Loads in the required models, textures and sounds.
    // ---------------------------------------------------------------------------------------
    World();

    // ---------------------------------------------------------------------------------------
    /// @brief World destructor that does cleaning up before the program quits. Frees the
    ///        memory allocated for models and sounds and cleans up the stl lists and vectors.
    // ---------------------------------------------------------------------------------------
    ~World();

    // ---------------------------------------------------------------------------------------
    /// @brief Generates and randomly distributes "stars" around the world between the planet
    ///        and the skybox. Stars (at least for now) are just simple GL_POINTS
    /// @param[in] _a Amount of stars to generate
    // ---------------------------------------------------------------------------------------
    void initStars(
                   const int _a
                  );

    // ---------------------------------------------------------------------------------------
    /// @brief Calls all the functions and displaylists that render and display the world.
    ///        Also calls the function that generates asteroids.
    // ---------------------------------------------------------------------------------------
    void drawWorld();

    // ---------------------------------------------------------------------------------------
    /// @brief Subdivides a triangle as many times as the user wants and calls the drawing
    ///        function in the end.
    /// @param[in] _a Point A of a triangle
    /// @param[in] _b Point B of a triangle
    /// @param[in] _c Point C of a triangle
    /// @param[in] _d Desired subdivisions / subdivision level
    // ---------------------------------------------------------------------------------------
    void subd(
              const Vec4 &_a,
              const Vec4 &_b,
              const Vec4 &_c,
              const int _d
             ) const;

  protected:
    // ---------------------------------------------------------------------------------------
    /// @brief Planet object that will generate the planet related stuff and that's used to
    ///        call the planet drawing inside drawWorld
    // ---------------------------------------------------------------------------------------
    Planet m_planet;

    // ---------------------------------------------------------------------------------------
    /// @brief Model structure holding the skybox data
    // ---------------------------------------------------------------------------------------
    model m_skybox;

    // ---------------------------------------------------------------------------------------
    /// @brief Model structure array holding the different asteroid meshes
    // ---------------------------------------------------------------------------------------
    model m_asteroid[2];

    // ---------------------------------------------------------------------------------------
    /// @brief stl vector holding the star positions
    // ---------------------------------------------------------------------------------------
    std::vector<Vec4> m_stars;

    // ---------------------------------------------------------------------------------------
    /// @brief stl vector holding the world displaylist (atmosphere, skybox)
    // ---------------------------------------------------------------------------------------
    std::vector<GLuint> m_wDisplayList;

    // ---------------------------------------------------------------------------------------
    /// @brief stl vector holding the displaylist of the asteroids
    // ---------------------------------------------------------------------------------------
    std::vector<GLuint> m_aDisplayList;

    // ---------------------------------------------------------------------------------------
    /// @brief Audio chunk holding the asteroid explosion sound data
    // ---------------------------------------------------------------------------------------
    Mix_Chunk *m_aExplosion;

    // ---------------------------------------------------------------------------------------
    /// @brief Audio chunk that'll hold the data for the actual background music
    // ---------------------------------------------------------------------------------------
    Mix_Chunk *m_bgMusic;

    // ---------------------------------------------------------------------------------------
    /// @brief GLuints that'll contain the skybox and asteroid textures respectively
    // ---------------------------------------------------------------------------------------
    GLuint m_skyBoxTexId, m_aTexId;

    // ---------------------------------------------------------------------------------------
    /// @brief Random number generator from boost random library
    // ---------------------------------------------------------------------------------------
    boost::mt19937 m_rng;

    // ---------------------------------------------------------------------------------------
    /// @brief Function that will draw the generated stars and set the opacity which for now
    ///        is only randomly generated, could implement the opacity (visibility) to depend
    ///        on the distance of the star.
    // ---------------------------------------------------------------------------------------
    void drawStars() const;

    // ---------------------------------------------------------------------------------------
    /// @brief Scales and calls the draw function from the planet object
    // ---------------------------------------------------------------------------------------
    void drawPlanet();

    // ---------------------------------------------------------------------------------------
    /// @brief Calls the tSphere function that subdivides an icosahedron to generate a
    ///        geodesic dome that will be displayed in wireframe mode (to have the look of the
    ///        original game for the atmosphere). Also scales the sphere and restores the fill
    ///        mode.
    // ---------------------------------------------------------------------------------------
    void atmosphere();

    // ---------------------------------------------------------------------------------------
    /// @brief Generates the displaylist from the skybox model (using a mesh here for the easy
    ///        texture coordinates), scales it and attaches a texture to it. Also disables
    ///        depth mask as nothing's behind the skybox so no need to check for what's behind
    ///        it.
    // ---------------------------------------------------------------------------------------
    void skybox();

    // ---------------------------------------------------------------------------------------
    /// @brief Uses boost random uniform int distribution to have asteroids spawn every now
    ///        and then if the amount of living asteroids has not exceeded the maximum value.
    ///        Uses the boost rng to generate a random starting position for an asteroid and
    ///        calculates the direction and randomly chooses a side vector for the asteroid
    ///        and calculates the up vector by taking the cross product of the position and
    ///        side vectors. The up and side vectors are used to calculate the movement when
    ///        the asteroid reaches the atmosphere. Also randomly generates a scale factor and
    ///        chooses the asteroid type. Lastly it the function handles the drawing and
    ///        destroyal of the asteroids.
    // ---------------------------------------------------------------------------------------
    void generate_Asteroids();

    // ---------------------------------------------------------------------------------------
    /// @brief Generates the displaylists from the asteroid meshes loaded in when the World
    ///        object was created
    // ---------------------------------------------------------------------------------------
    void genALists();

    // ---------------------------------------------------------------------------------------
    /// @brief Geodesic sphere "generator". Uses the icosahedron shape define in Icosahedron.h
    ///        to run through the triangles defined, subdivides them and normalises the new
    ///        verts to generate a spherical shape.
    /// @param[in] _d Desired subdivision levels
    // ---------------------------------------------------------------------------------------
    void tSphere(
                 const int _d
                ) const;

    // ---------------------------------------------------------------------------------------
    /// @brief Draws a triangle from the given vertices (Vec4), also generates a normal vector
    ///        by adding the three vertex vectors together and normalising the resulting vector.
    /// @param[in] _a First vertex of the triangle
    /// @param[in] _b Second vertex of the triangle
    /// @param[in] _c Third vertex of the triangle
    // ---------------------------------------------------------------------------------------
    void drawTriangle(
                      const Vec4 &_a,
                      const Vec4 &_b,
                      const Vec4 &_c
                     ) const;

    // ---------------------------------------------------------------------------------------
    /// @brief Does simple spatial partitioning on the asteroids by checking the distance of
    ///        each asteroid from the origin and records the indices of the asteroids that
    ///        have reached the atmosphere, this is then used to only check collisions on the
    ///        asteroids are on the atmosphere.
    // ---------------------------------------------------------------------------------------
    void partByDist();

}; // end of class

#endif // end of WORLD_H
