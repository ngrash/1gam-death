#include "player.h"

#define MAX_PLAYER_VELOCITY_X 50

Player::Player(Resources& resources) :
  velocity_x_factor_(0),
  resources_(resources)
{
  animation_->frame_duration = 0.10;
  animation_->texture = resources_.GetTexture(Texture::PLAYER_IDLE);

  position_.x = 40;
  position_.y = 50;
}

void Player::SetVelocityXFactor(float factor) {
  if(velocity_x_factor_ != factor) {
    velocity_x_factor_ = factor;

    velocity_.x = MAX_PLAYER_VELOCITY_X * factor;

    animation_->Reset();

    if(factor == 0) {
      animation_->texture = resources_.GetTexture(Texture::PLAYER_IDLE);
      animation_->num_frames = 0;
    } else if(factor > 0) {
      animation_->texture = resources_.GetTexture(Texture::PLAYER_WALKING);
      animation_->render_flip = SDL_FLIP_NONE;
      animation_->num_frames = 4;
    } else if(factor < 0) {
      animation_->texture = resources_.GetTexture(Texture::PLAYER_WALKING);
      animation_->render_flip = SDL_FLIP_HORIZONTAL;
      animation_->num_frames = 4;
    }
  }
}

void Player::Update(float seconds_elapsed) {
  animation_->Update(seconds_elapsed);

  velocity_.x += acceleration_.x * seconds_elapsed;
  velocity_.y += acceleration_.y * seconds_elapsed;

  position_.x += velocity_.x * seconds_elapsed;
  position_.y += velocity_.y * seconds_elapsed;
}
