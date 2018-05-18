#include "zombie.h"

#include "animation.h"

#define ZOMBIE_SPEED 30

Zombie::Zombie(Resources& resources) {
  animation_->frame_duration = 0.25;
  animation_->texture = resources.GetTexture(Texture::ZOMBIE_WALKING);
  animation_->num_frames = 4;

  x_ = 90;
  y_ = 70;
}

void Zombie::Update(float seconds_elapsed) {
  animation_->Update(seconds_elapsed);
}
