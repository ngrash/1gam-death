#include "zombie_state_dying.h"

#include "zombie.h"

void ZombieStateDying::Initialize(Zombie& zombie) {
  state_duration_ = 0;
  zombie.animation_->Reset();
  zombie.animation_->texture = zombie.world_.GetResources().GetTexture(Texture::ZOMBIE_DYING);
  zombie.animation_->frame_duration = 0.10;
  zombie.animation_->num_frames = 2;
}

void ZombieStateDying::Update(float seconds_elapsed, Zombie& zombie) {
  zombie.animation_->Update(seconds_elapsed);

  state_duration_ += seconds_elapsed;
  if(state_duration_ >= 0.2) {
    zombie.SetState(zombie.state_dead_);
  }
}
