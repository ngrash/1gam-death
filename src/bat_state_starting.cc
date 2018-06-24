#include "bat_state_starting.h"

#include "bat.h"

void BatStateStarting::Initialize(Bat& bat) {
  state_duration_ = 0;
  bat.animation_->Reset();
  bat.animation_->texture = bat.world_.GetResources().GetTexture(Texture::BAT_STARTING);
  bat.animation_->frame_duration = 0.1f;
  bat.animation_->num_frames = 3;
}

void BatStateStarting::Update(float seconds_elapsed, Bat& bat) {
  bat.animation_->Update(seconds_elapsed);

  bat.position_.y -= 30 * seconds_elapsed;
  bat.position_.x += 10 * seconds_elapsed;

  state_duration_ += seconds_elapsed;
  if(state_duration_ >= 0.5) {
    bat.SetState(bat.state_flying_);
  }
}
