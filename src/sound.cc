#include "sound.h"

#include "logging.h"

Sound::Sound() :
  samples_((int)Sample::_LAST_ELEMENT_, nullptr),
  music_((int)Sample::_LAST_ELEMENT_, nullptr)
{}

Sound::~Sound() {
  DestroySamples();
}

Mix_Chunk* Sound::LoadSample(Sample sample) {
  switch(sample) {
    case Sample::NO_AMMO:
      return LoadSample("assets/no_ammo.wav");
    case Sample::SHOT:
      return LoadSample("assets/shot.wav");
    case Sample::DAMAGE:
      return LoadSample("assets/damage.wav");
    case Sample::_LAST_ELEMENT_:
    default:
      return nullptr;
  }
}

Mix_Music* Sound::LoadMusic(Music music) {
  switch(music) {
    case Music::LEVEL_1_LOOP:
      return LoadMusic("assets/lvl1_loop.wav");
    case Music::LEVEL_2_LOOP:
      return LoadMusic("assets/lvl2_loop.wav");
    case Music::_LAST_ELEMENT_:
    default:
      return nullptr;
  }
}

void Sound::PlaySample(Sample sample) {
  Mix_Chunk* chunk = GetSample(sample);
  if(Mix_PlayChannel(-1, chunk, 0) == -1) {
    logMixError("Mix_PlayChannel");
  }
}

void Sound::PlayMusic(Music music) {
  Mix_Music* mix_music = GetMusic(music);
  if(Mix_PlayMusic(mix_music, -1) == -1) {
    logMixError("Mix_PlayMusic");
  }
}

Mix_Chunk* Sound::GetSample(Sample sample) {
  if(samples_[int(sample)] == nullptr) {
    samples_[int(sample)] = LoadSample(sample);
  }
  return samples_[int(sample)];
}

Mix_Music* Sound::GetMusic(Music music) {
  if(music_[int(music)] == nullptr) {
    music_[int(music)] = LoadMusic(music);
  }
  return music_[int(music)];
}

void Sound::DestroySamples() {
  for(int i = 0; i < (int)Sample::_LAST_ELEMENT_; i++) {
    if(samples_[i] != nullptr) {
      Mix_FreeChunk(samples_[i]);
      samples_[i] = nullptr;
    }
  }
}

void Sound::DestroyMusic() {
  for(int i = 0; i < (int)Music::_LAST_ELEMENT_; i++) {
    if(music_[i] != nullptr) {
      Mix_FreeMusic(music_[i]);
      music_[i] = nullptr;
    }
  }
}

Mix_Chunk* Sound::LoadSample(const std::string& file) {
  Mix_Chunk* chunk = Mix_LoadWAV(file.c_str());
  if(chunk == nullptr) {
    logMixError("Mix_LoadWAV");
  }
  return chunk;
}

Mix_Music* Sound::LoadMusic(const std::string& file) {
  Mix_Music* music = Mix_LoadMUS(file.c_str());
  if(music == nullptr) {
    logMixError("Mix_LoadMUS");
  }
  return music;
}
