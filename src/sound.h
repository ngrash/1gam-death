#ifndef SOUND_H_
#define SOUND_H_

#include <vector>
#include <string>

#include "SDL2/SDL_mixer.h"

enum class Sample {
  NO_AMMO,
  _LAST_ELEMENT_
};

class Sound {
  public:
    Sound();
    ~Sound();
    void PlaySample(Sample sample);

  private:
    std::vector<Mix_Chunk*> samples_;
    void DestroySamples();

    Mix_Chunk* GetSample(Sample sample);
    Mix_Chunk* LoadSample(Sample sample);
    Mix_Chunk* LoadSample(const std::string& file);
};

#endif // SOUND_H_
