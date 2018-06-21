#include "bat_state_attacking.h"

#include "bat.h"

#define FRAME_DURATION 0.5
#define NUM_FRAMES 1
#define SPEED 30
#define DAMAGE 1

void BatStateAttacking::Initialize(Bat& bat) {
  state_duration_ = 0;
  dealt_damage_ = false;
  bat.animation_->Reset();
  bat.animation_->texture = bat.world_.GetResources().GetTexture(Texture::BAT_ATTACKING);
  bat.animation_->frame_duration = FRAME_DURATION;
  bat.animation_->num_frames = NUM_FRAMES;
}

void BatStateAttacking::Update(float seconds_elapsed, Bat& bat) {
  bat.animation_->Update(seconds_elapsed);

  bat.position_.x += SPEED * seconds_elapsed;
  bat.position_.y -= 10 * seconds_elapsed;
  if(bat.position_.y <= 16) {
    bat.position_.y = 16;
  }

  state_duration_ += seconds_elapsed;

  if(!dealt_damage_) {
    if(bat.world_.GetCollisions().DoCollide(&bat, &bat.world_.GetPlayer())) {
      dealt_damage_ = true;

      bat.world_.GetPlayer().health_ -= DAMAGE;
    }
  }

  if(state_duration_ >= FRAME_DURATION * NUM_FRAMES) {
    bat.SetState(bat.state_flying_);
  }
}
