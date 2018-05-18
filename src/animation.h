#ifndef ANIMATION_H_
#define ANIMATION_H_

#include "SDL2/SDL.h"
#include "sprite.h"

class Animation : public Sprite {
  public:
    Animation();
    void Reset();
    void Update(float seconds_elapsed);
    int num_frames;
    float frame_duration;
  private:
    int current_frame_;
    float current_frame_duration_;
};

#endif // ANIMATION_H_
