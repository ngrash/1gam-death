#include "zombie.h"

#include <cmath>

#include "vector2f.h"

#define MAX_ZOMBIE_VELOCITY_X 10
#define DESIRED_DISTANCE_TO_PLAYER 6

Zombie::Zombie(Player& player, Resources& resources) :
  player_(player),
  resources_(resources)
{
  animation_->frame_duration = 0.25;
  animation_->texture = resources_.GetTexture(Texture::ZOMBIE_WALKING);
  animation_->num_frames = 4;

  position_.x = 90;
  position_.y = 50;
}

void Zombie::Update(float seconds_elapsed) {
  animation_->Update(seconds_elapsed);

  Vector2f player_pos = player_.GetPosition();

  if(player_pos.x > position_.x) {
    animation_->render_flip = SDL_FLIP_NONE;
    velocity_.x = MAX_ZOMBIE_VELOCITY_X;
  }
  else if(player_pos.y < position_.x) {
    animation_->render_flip = SDL_FLIP_HORIZONTAL;
    velocity_.x = -MAX_ZOMBIE_VELOCITY_X;
  }

  float distance_to_player = abs(player_pos.x - position_.x);
  bool reached_player = distance_to_player <= DESIRED_DISTANCE_TO_PLAYER;

  if(reached_player) {
      animation_->texture = resources_.GetTexture(Texture::ZOMBIE_IDLE);
      animation_->num_frames = 0;
      animation_->Reset();
  } else {
      animation_->texture = resources_.GetTexture(Texture::ZOMBIE_WALKING);
      animation_->num_frames = 4;

      position_.x += velocity_.x * seconds_elapsed;
  }
}
