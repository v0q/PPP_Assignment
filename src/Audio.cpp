/*
 Copyright © 2015 Teemu Lindborg
 SDAGE 1st year 2nd PPP Assignment
*/

#include <string>

#include "Audio.h"

// ---------------------------------------------------------------------------------------
/// @file Audio.cpp
/// @brief Implementation of the audio loading functions
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------
void audio::loadSound(
                      const std::string &_fname,
                      Mix_Chunk **o_sound
                     )
{
  // Load the audio file and check that the loading succeeded
  // if not then print out an error
  *o_sound = Mix_LoadWAV(_fname.c_str());
  if(*o_sound == NULL)
    std::cerr << "Unable to load the sound file: " << Mix_GetError() << "\n";
}
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------
void audio::loadSound(
                      const std::string &_fname,
                      Mix_Music **o_music
                     )
{
  // Load the music file and check that the loading succeeded
  // if not then print out an error
  *o_music = Mix_LoadMUS(_fname.c_str());
  if(*o_music == NULL)
    std::cerr << "Unable to load the sound file: " << Mix_GetError() << "\n";
}
// ---------------------------------------------------------------------------------------
