#include "zombie_state_rising.h"

#include "zombie.h"

void ZombieStateRising::Initialize(Zombie& zombie) {
  state_duration_ = 0;
  zombie.animation_->Reset();
  zombie.animation_->texture = zombie.world_.GetResources().GetTexture(Texture::ZOMBIE_RISING);
  zombie.animation_->frame_duration = 0.25;
  zombie.animation_->num_frames = 4;
}

void ZombieStateRising::Update(float seconds_elapsed, Zombie& zombie) {
  zombie.animation_->Update(seconds_elapsed);

  state_duration_ += seconds_elapsed;
  if(state_duration_ >= 1) {
    zombie.SetState(zombie.state_chasing_);
  }
}
