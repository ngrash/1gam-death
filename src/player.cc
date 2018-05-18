#include "player.h"

#define PLAYER_SPEED 50

Player::Player(Resources& resources) :
  velocityFactor_(0),
  resources_(resources),
  current_frame_duration_(0),
  current_frame_(0),
  num_frames_(0)
{
  animation_->frame_duration = 0.25;
  animation_->texture = resources_.GetTexture(Texture::PLAYER_IDLE);

  x_ = 50;
  y_ = 70;
}

void Player::SetVelocity(float factor) {
  if(factor != velocityFactor_) {
    velocityFactor_ = factor;

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

  x_ += PLAYER_SPEED * velocityFactor_ * seconds_elapsed;
}
