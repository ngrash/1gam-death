#include "bat_state_attacking.h"

#include "bat.h"

void BatStateAttacking::Initialize(Bat& bat) {
  state_duration_ = 0;
  dealt_damage_ = false;
  bat.animation_->Reset();
  bat.animation_->texture = bat.resources_.GetTexture(Texture::BAT_ATTACKING);
  bat.animation_->frame_duration = 0.3;
  bat.animation_->num_frames = 1;
}

void BatStateAttacking::Update(float seconds_elapsed, Bat& bat) {
  bat.animation_->Update(seconds_elapsed);

  state_duration_ += seconds_elapsed;

  if(!dealt_damage_) {
    // TODO: Check collision

    dealt_damage_ = true;
  }
}
