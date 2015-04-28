#include "Audio.h"

void audio::loadSound(const std::string &_fname, Mix_Chunk **_sound)
{
  *_sound = Mix_LoadWAV(_fname.c_str());
  if(*_sound == NULL)
    std::cerr << "Unable to load the sound file: " << Mix_GetError() << "\n";
}

void audio::loadSound(const std::string &_fname, Mix_Music **_music)
{
  *_music = Mix_LoadMUS(_fname.c_str());
  if(*_music == NULL)
    std::cerr << "Unable to load the sound file: " << Mix_GetError() << "\n";
}
