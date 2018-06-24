#include "zombie_state_dead.h"

#include "zombie.h"

void ZombieStateDead::Initialize(Zombie& zombie) {
  state_duration_ = 0;
  zombie.animation_->Reset();
  zombie.animation_->texture = zombie.world_.GetResources().GetTexture(Texture::ZOMBIE_DEAD);
  zombie.animation_->frame_duration = 0;
  zombie.animation_->num_frames = 0;
  zombie.hitbox_.h = 1;

  // make sure they don't flicker on the ground
  zombie.position_.x = (int)zombie.position_.x;
  zombie.position_.y = (int)zombie.position_.y;
}

void ZombieStateDead::Update(float, Zombie&) {}
