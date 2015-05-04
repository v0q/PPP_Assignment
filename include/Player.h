/*
 Copyright © 2015 Teemu Lindborg
 SDAGE 1st year 2nd PPP Assignment
*/

#ifndef PLAYER_H
#define PLAYER_H

// ---------------------------------------------------------------------------------------
/// @file Player.h
/// @brief Player class that holds all the player's functionality like movement, shooting
///
/// @version 1.0
/// @author Teemu Lindborg
/// @date 03/05/15
/// Revision History:
///   -
/// @todo Tidy the code a lot. Reorganize and possibly divide some of the functionality to
///       separate classes/files, like explosions, collision detection.
// ---------------------------------------------------------------------------------------

#ifdef LINUX
  #include <GL/gl.h>
#endif
#ifdef DARWIN
  #include <OpenGL/gl.h>
#endif

#include <SDL2/SDL.h>
#include <vector>
#include <list>

#include "Camera.h"
#include "Audio.h"
#include "Projectile.h"
#include "LoadOBJ.h"
#include "TextureOBJ.h"
#include "Asteroids.h"
#include "NCCA/Vec4.h"

// This will be used to lift the player a bit above the planet's surface
#define PLAYEROFFSET 0.1f

// Sensitivity for the game controller, should eliminate minor "noise" when
// the controller sticks not touched.
const int sensitivity = 6000;

class Player
{
  public:
    // ---------------------------------------------------------------------------------------
    /// @brief stl vector holding the live particles that are born from collision:
    ///        asteroid-projectile &
    ///        asteroid-player
    // ---------------------------------------------------------------------------------------
    std::vector<Particle> particles;

    // ---------------------------------------------------------------------------------------
    /// @brief Player's score
    // ---------------------------------------------------------------------------------------
    int score;

    // ---------------------------------------------------------------------------------------
    /// @brief Constructor for the player that loads the model, textures, audio and initialises
    ///        the player class member variables
    /// @param[in] _x Initial x pos
    /// @param[in] _y Initial y pos
    /// @param[in] _z Initial z pos
    // ---------------------------------------------------------------------------------------
    Player(
           const float _x = 1.0f,
           const float _y = 1.0f,
           const float _z = 1.0f
          );

    // ---------------------------------------------------------------------------------------
    /// @brief Default dtor, clears the projectile and particle vectors, frees the memory
    ///        allocated for the ship model and audio
    // ---------------------------------------------------------------------------------------
    ~Player();

    // ---------------------------------------------------------------------------------------
    /// @brief Checks the player's health and returns whether the player's still alive
    /// @return True if player's health > 0, false otherwise
    // ---------------------------------------------------------------------------------------
    bool isAlive();

    // ---------------------------------------------------------------------------------------
    /// @brief Calls the displaylist with the ship model in and handles the translates and
    ///        rotations of the player
    // ---------------------------------------------------------------------------------------
    void drawPlayer();

    // ---------------------------------------------------------------------------------------
    /// @brief Handles the movement of the player (camera) and calculates the new up and side
    ///        vectors for both. Calculates the rotation and tilting of the ship. Also
    ///        calculates the little movement of the shipthat simulates the effect where it
    ///        takes a short while for the camera to catch up with the movement of the player.
    /// @param[in] _c Holds the game controller structure, if this is NULL keyboard is used instead
    /// @param[io] io_cam Camera that's position will be updated (the camera actually moves and the
    ///             player is just positioned in front of it)
    // ---------------------------------------------------------------------------------------
    void handleMovement(
                        SDL_GameController *_c,
                        Camera &io_cam
                       );

    // ---------------------------------------------------------------------------------------
    /// @brief Checks for collisions between player-asteroids and projectiles-asteroids.
    ///        A primitive spatial partitioning is used where the collisions are only
    ///        checked against asteroids that have reached the atmosphere.
    /// @param[io] io_a stl vector holding all the asteroids
    /// @param[io] io_aInd stl list holding the indices of the asteroids that have reached
    ///                the atmosphere
    // ---------------------------------------------------------------------------------------
    void checkCollisions(
                         std::vector<Asteroid> &io_a,
                         std::list<int> &io_aInd
                        );

    // ---------------------------------------------------------------------------------------
    /// @brief Runs through the living particles vector calls for the draw and move functions
    ///        of a particle, also increases the elapsed life and checks whether it has reached
    ///        the max lifespan of the particle. Kills the particles when they've reach the max
    ///        life.
    // ---------------------------------------------------------------------------------------
    void drawParticles();

  protected:
    // ---------------------------------------------------------------------------------------
    /// @brief Vector storing the player's position. Used for collision detection.
    // ---------------------------------------------------------------------------------------
    Vec4 pos;

    // ---------------------------------------------------------------------------------------
    /// @brief Mat4 matrix where the camera's orientation is stored in, this is then used to
    ///        orient/place the player in front of the camera using glMultMatrixf().
    // ---------------------------------------------------------------------------------------
    Mat4 orientation;

    // ---------------------------------------------------------------------------------------
    /// @brief Model structure holding the ship model data.
    // ---------------------------------------------------------------------------------------
    model m_ship;

    // ---------------------------------------------------------------------------------------
    /// @brief stl vector storing the living projectile data.
    // ---------------------------------------------------------------------------------------
    std::vector<Projectile> p;

    // ---------------------------------------------------------------------------------------
    /// @brief stl vector holding displaylist for the ship
    // ---------------------------------------------------------------------------------------
    std::vector<GLuint> m_displayList;

    // ---------------------------------------------------------------------------------------
    /// @brief Audio chunk for the firing sound
    // ---------------------------------------------------------------------------------------
    Mix_Chunk *a_fire;

    // ---------------------------------------------------------------------------------------
    /// @brief Music data storing the noise that's played when the player moves
    // ---------------------------------------------------------------------------------------
    Mix_Music *bgSound;

    // ---------------------------------------------------------------------------------------
    /// @brief Aim direction angle for shooting
    // ---------------------------------------------------------------------------------------
    float aimDir;

    // ---------------------------------------------------------------------------------------
    /// @brief Rotation of the player (changes when the player changes direction)
    // ---------------------------------------------------------------------------------------
    float rot;

    // ---------------------------------------------------------------------------------------
    /// @brief Tilt angle of the ship when player is turning
    // ---------------------------------------------------------------------------------------
    float turn;

    // ---------------------------------------------------------------------------------------
    /// @brief Variables used to translate the player from the dead center of the view to
    ///        simulate the camera trying to catch up with the player when they're moving.
    // ---------------------------------------------------------------------------------------
    float xMov, yMov;

    // ---------------------------------------------------------------------------------------
    /// @brief Player's health, used to check if player's alive or not.
    // ---------------------------------------------------------------------------------------
    int life;

    // ---------------------------------------------------------------------------------------
    /// @brief Used to store the texture data of the ship
    // ---------------------------------------------------------------------------------------
    GLuint shipTexId;

    // ---------------------------------------------------------------------------------------
    /// @brief Used to store the texture data of the projectiles
    // ---------------------------------------------------------------------------------------
    GLuint projectileId;

    // ---------------------------------------------------------------------------------------
    /// @brief Used to store the texture data of the fire particles
    // ---------------------------------------------------------------------------------------
    GLuint particleTexId;

    // ---------------------------------------------------------------------------------------
    /// @brief Generates the ship's displaylist from the model data
    // ---------------------------------------------------------------------------------------
    void ship();

    // ---------------------------------------------------------------------------------------
    /// @brief Wraps degrees to positive values between 0 & 360
    /// @param[io] io_a Degree to be wrapped
    // ---------------------------------------------------------------------------------------
    void wrapRotation(
                      float &io_a
                     );

    // ---------------------------------------------------------------------------------------
    /// @brief Handles the actual shooting, whenever the player is shooting pushes projectiles
    ///        in to the stl vector and stores the players current position, up, left and
    ///        normal vectors, aim direction
    /// @param[in] _c Game controller structure, used as the primary device controlling device
    ///               if it's not NULL
    /// @param[in] _cu Camera's current up vector
    /// @param[in] _cl Camera's current left vector
    // ---------------------------------------------------------------------------------------
    void shoot(
               SDL_GameController *_c,
               const Vec4 &_cu,
               const Vec4 &_cl
              );

};

#endif
