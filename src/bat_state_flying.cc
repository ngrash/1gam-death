#include "bat_state_flying.h"

#include "bat.h"

#define FRAME_DURATION 0.07f
#define NUM_FRAMES 4
#define SPEED 40
#define ATTACK_DISTANCE 10

void BatStateFlying::Initialize(Bat& bat) {
  bat.animation_->Reset();
  bat.animation_->texture = bat.world_.GetResources().GetTexture(Texture::BAT_FLYING);
  bat.animation_->frame_duration = FRAME_DURATION;
  bat.animation_->num_frames = NUM_FRAMES;
}

void BatStateFlying::Update(float seconds_elapsed, Bat& bat) {
  bat.animation_->Update(seconds_elapsed);

  bat.position_.x += SPEED * seconds_elapsed;

  if(bat.position_.x < bat.world_.GetPlayer().position_.x && bat.world_.GetDistanceToPlayer(&bat) <= ATTACK_DISTANCE) {
    bat.SetState(bat.state_attacking_);
  }
}
