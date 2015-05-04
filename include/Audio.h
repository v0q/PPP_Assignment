/*
 Copyright © 2015 Teemu Lindborg
 SDAGE 1st year 2nd PPP Assignment
*/

#ifndef AUDIO_H
#define AUDIO_H

// ---------------------------------------------------------------------------------------
/// @file Audio.h
/// @brief Functions to load in audio files
/// @version 1.0
/// @author Teemu Lindborg
/// @date 03/05/15
/// Revision History:
///   -
/// @todo Nothing for now
// ---------------------------------------------------------------------------------------

#include <iostream>
#include <SDL2/SDL_mixer.h>

namespace audio
{
  // ---------------------------------------------------------------------------------------
  /// @brief Loads an audio file to Mix_Chunk
  /// @param[in] _fname Path to the sound file
  /// @param[out] o_sound Var to store the sound data
  // ---------------------------------------------------------------------------------------
  void loadSound(
                 const std::string &_fname,
                 Mix_Chunk **o_sound
                );

  // ---------------------------------------------------------------------------------------
  /// @brief Loads a music file to Mix_Music
  /// @param[in] _fname Path to the music file
  /// @param[out] o_music Var to store the music data
  // ---------------------------------------------------------------------------------------
  void loadSound(
                 const std::string &_fname,
                 Mix_Music **o_music
                );
} // end of namespace

#endif // end of AUDIO_H
