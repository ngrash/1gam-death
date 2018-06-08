#ifndef SOUND_H_
#define SOUND_H_

#include <vector>
#include <string>

#include "SDL2/SDL_mixer.h"

enum class Sample {
  NO_AMMO,
  DAMAGE,
  SHOT,
  _LAST_ELEMENT_
};

enum class Music {
  LEVEL_1_LOOP,
  _LAST_ELEMENT_
};

class Sound {
  public:
    Sound();
    ~Sound();
    void PlaySample(Sample sample);
    void PlayMusic(Music music);

  private:
    std::vector<Mix_Chunk*> samples_;
    std::vector<Mix_Music*> music_;

    void DestroySamples();
    void DestroyMusic();

    Mix_Chunk* GetSample(Sample sample);
    Mix_Chunk* LoadSample(Sample sample);
    Mix_Chunk* LoadSample(const std::string& file);

    Mix_Music* GetMusic(Music music);
    Mix_Music* LoadMusic(Music music);
    Mix_Music* LoadMusic(const std::string& file);
};

#endif // SOUND_H_
