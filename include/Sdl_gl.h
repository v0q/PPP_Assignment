/*
 Copyright © 2015 Teemu Lindborg
 SDAGE 1st year 2nd PPP Assignment
*/

#ifndef SDL_GL_H
#define SDL_GL_H

// ---------------------------------------------------------------------------------------
/// @file Sdl_gl.h
/// @brief Class that handles the creation of the SDL/OpenGL window and context, also
///        used to handle most of the SDL functionality, like general input,
///        initialisation of SDL, Game controller, SDL2_mixer, glut (required on Linux),
///        lighting
/// @version 1.0
/// @author Teemu Lindborg
/// @date 03/05/15
/// Revision History:
///   -
/// @todo Tidying up, not necessarily the cleanest way to handle all of this but
///       made the main function a lot neater. Figure out the best way to do this.
// ---------------------------------------------------------------------------------------

#ifdef LINUX
  #include <GL/gl.h>
#endif
#ifdef DARWIN
  #include <OpenGL/gl.h>
#endif

#include <SDL2/SDL.h>
#include <iostream>

#include "Camera.h"
#include "Player.h"
#include "World.h"

class SDL_GL
{
  public:
    // ---------------------------------------------------------------------------------------
    /// @brief SDL_window that will display our game. Also the gl context will be rendering
    ///        everything to this window
    // ---------------------------------------------------------------------------------------
    SDL_Window *m_win;

    // ---------------------------------------------------------------------------------------
    /// @brief Structure that'll hold the controller attributes, should one be available.
    ///        NULL otherwise.
    // ---------------------------------------------------------------------------------------
    SDL_GameController *m_controller;

    // ---------------------------------------------------------------------------------------
    /// @brief Constructor that initialises SDL systems, Game controller subsystem, SDL mixer.
    ///        Creates the SDL window, gl context and allows the game to run should all the
    ///        necessary things start correctly.
    // ---------------------------------------------------------------------------------------
    SDL_GL();

    // ---------------------------------------------------------------------------------------
    /// @brief Default dtor that closes the opened systems and deletes the gl context.
    ///        Cleans up the SDL and GL stuff.
    // ---------------------------------------------------------------------------------------
    ~SDL_GL();

    // ---------------------------------------------------------------------------------------
    /// @brief Functions that quits SDL and exits printing out the error message should
    ///        something not initialise properly
    /// @param _msg Message to be printed before the SDL error
    // ---------------------------------------------------------------------------------------
    void SDLErrorExit(
                      const std::string &_msg
                     );

    // ---------------------------------------------------------------------------------------
    /// @brief Enables the lights and some texture related things like GL_POINT_SPRITE
    ///        GL_BLEND and so on.
    // ---------------------------------------------------------------------------------------
    void enableLighting() const;

    // ---------------------------------------------------------------------------------------
    /// @brief Checks if the main loop should be running, i.e. the game's active
    /// @return True if the game should be running, false it we want to quit the program
    // ---------------------------------------------------------------------------------------
    bool isActive() const;

    // ---------------------------------------------------------------------------------------
    /// @brief Handles basic input and calls the functions that handle movement etc.
    /// @param[io] io_p Player object so we can call the movement functions
    /// @param[io] io_cam Camera object to be used for movement and calculations
    // ---------------------------------------------------------------------------------------
    void handleInput(
                     Player &io_p,
                     Camera &io_cam
                    );

  protected:
    // ---------------------------------------------------------------------------------------
    /// @brief gl GLContext that we'll use to create the gl context
    // ---------------------------------------------------------------------------------------
    SDL_GLContext m_gl;

    // ---------------------------------------------------------------------------------------
    /// @brief Variable telling whether the program should be running or not
    // ---------------------------------------------------------------------------------------
    bool m_act;

    // ---------------------------------------------------------------------------------------
    /// @brief Creates the GL Context
    /// @return Returns the created context
    // ---------------------------------------------------------------------------------------
    SDL_GLContext createOpenGLContext();
}; // end of class

#endif // end of SDL_GL_H
