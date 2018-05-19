#include "zombie.h"

#include <cmath>

#include "animation.h"

#define ZOMBIE_SPEED 10
#define DESIRED_DISTANCE 6

Zombie::Zombie(Player& player, Resources& resources) :
  player_(player),
  resources_(resources)
{
  animation_->frame_duration = 0.25;
  animation_->texture = resources_.GetTexture(Texture::ZOMBIE_WALKING);
  animation_->num_frames = 4;

  x_ = 90;
  y_ = 70;
}

void Zombie::Update(float seconds_elapsed) {
  animation_->Update(seconds_elapsed);

  float velocityX = 0;
  if(player_.GetX() > x_) {
    animation_->render_flip = SDL_FLIP_NONE;
    velocityX = 1.0;
  }
  else if(player_.GetX() < x_) {
    animation_->render_flip = SDL_FLIP_HORIZONTAL;
    velocityX = -1.0;
  }

  float distanceToPlayer = abs(player_.GetX() - x_);
  bool reachedPlayer = distanceToPlayer <= DESIRED_DISTANCE;

  if(reachedPlayer) {
      animation_->texture = resources_.GetTexture(Texture::ZOMBIE_IDLE);
      animation_->num_frames = 0;
      animation_->Reset();
  } else {
      animation_->texture = resources_.GetTexture(Texture::ZOMBIE_WALKING);
      animation_->num_frames = 4;

      x_ += ZOMBIE_SPEED * velocityX * seconds_elapsed;
  }
}
