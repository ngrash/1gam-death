#include "zombie_state_attacking.h"

#include "zombie.h"

void ZombieStateAttacking::Initialize(Zombie& zombie) {
  state_duration_ = 0;
  zombie.animation_->Reset();
  zombie.animation_->texture = zombie.resources_.GetTexture(Texture::ZOMBIE_ATTACKING);
  zombie.animation_->frame_duration = 0.5;
  zombie.animation_->num_frames = 2;
}

void ZombieStateAttacking::Update(float seconds_elapsed, Zombie& zombie) {
  zombie.animation_->Update(seconds_elapsed);

  state_duration_ += seconds_elapsed;
  if(state_duration_ >= 1) {
    zombie.SetState(zombie.state_chasing_);
  }
}
