#include "bat_state_flying.h"

#include "bat.h"

void BatStateFlying::Initialize(Bat& bat) {
  bat.animation_->Reset();
  bat.animation_->texture = bat.resources_.GetTexture(Texture::BAT_FLYING);
  bat.animation_->frame_duration = 0.07;
  bat.animation_->num_frames = 4;
}

void BatStateFlying::Update(float seconds_elapsed, Bat& bat) {
  bat.animation_->Update(seconds_elapsed);

  bat.position_.x += 40 * seconds_elapsed;
}
