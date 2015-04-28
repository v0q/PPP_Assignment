#ifndef AUDIO_H
#define AUDIO_H

#include <iostream>
#include <SDL2/SDL_mixer.h>

namespace audio
{
  void loadSound(const std::string &_fname, Mix_Chunk **_sound);
  void loadSound(const std::string &_fname, Mix_Music **_music);
}

/*void loadSounds(Mix_Chunk *o_music[4], Mix_Chunk **o_shoot, Mix_Chunk **o_invaderkilled, Mix_Chunk **o_ufo_lp, Mix_Chunk **o_explosion);
void playSound(Mix_Chunk *_sound, int _chanToPlay, int _loops);
void playMusic(int _gameSpeed, Mix_Chunk *_music[4]);
void freeSounds(Mix_Chunk *_music[4], Mix_Chunk **_shoot, Mix_Chunk **_invaderkilled, Mix_Chunk **_ufo_lowpitch, Mix_Chunk **_explosion);*/

#endif
