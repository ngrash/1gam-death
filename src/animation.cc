#include "animation.h"

Animation::Animation()
{
  render_flip = SDL_FLIP_NONE;
  src_rect.x = 0;
  src_rect.y = 0;
  src_rect.w = 16;
  src_rect.h = 16;
}

void Animation::Reset() {
  src_rect.x = 0;
  current_frame_ = 0;
  current_frame_duration_ = 0;
}

void Animation::Update(float seconds_elapsed) {
  current_frame_duration_ += seconds_elapsed;
  if(current_frame_duration_ >= frame_duration) {

    current_frame_++;
    if(current_frame_ >= num_frames) {
      current_frame_ = 0;
    }

    this->src_rect.x = current_frame_ * 16;
    current_frame_duration_ = 0;
  }
}
