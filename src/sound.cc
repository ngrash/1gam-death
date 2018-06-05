#include "sound.h"

#include "logging.h"

Sound::Sound() :
  samples_((int)Sample::_LAST_ELEMENT_, nullptr)
{}

Sound::~Sound() {
  DestroySamples();
}

Mix_Chunk* Sound::LoadSample(Sample sample) {
  switch(sample) {
    case Sample::NO_AMMO:
      return LoadSample("assets/no_ammo.wav");
    case Sample::_LAST_ELEMENT_:
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

Mix_Chunk* Sound::GetSample(Sample sample) {
  if(samples_[int(sample)] == nullptr) {
    samples_[int(sample)] = LoadSample(sample);
  }
  return samples_[int(sample)];
}

void Sound::DestroySamples() {
  for(int i = 0; i < (int)Sample::_LAST_ELEMENT_; i++) {
    if(samples_[i] != nullptr) {
      Mix_FreeChunk(samples_[i]);
      samples_[i] = nullptr;
    }
  }
}

Mix_Chunk* Sound::LoadSample(const std::string& file) {
  Mix_Chunk* chunk = Mix_LoadWAV(file.c_str());
  if(chunk == nullptr) {
    logMixError("LoadSample");
  }

  return chunk;
}
