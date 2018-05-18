#include "player.h"

#define PLAYER_SPEED 50

Player::Player(Resources& resources) :
  velocityFactor_(0),
  resources_(resources),
  current_frame_duration_(0),
  current_frame_(0),
  num_frames_(0)
{
  sprite_ = new Sprite();
  sprite_->render_flip = SDL_FLIP_NONE;
  sprite_->texture = resources_.GetTexture(Texture::PLAYER_IDLE);
  sprite_->src_rect.x = 0;
  sprite_->src_rect.y = 0;
  sprite_->src_rect.w = 16;
  sprite_->src_rect.h = 16;

  x_ = 50;
  y_ = 70;
}

Player::~Player() {
  delete sprite_;
}

Sprite* Player::GetSprite() {
  return sprite_;
}

void Player::SetVelocity(float factor) {
  if(factor != velocityFactor_) {
    velocityFactor_ = factor;

    sprite_->src_rect.x = 0;

    if(factor == 0) {
      sprite_->texture = resources_.GetTexture(Texture::PLAYER_IDLE);
      num_frames_ = 0;
    } else if(factor > 0) {
      sprite_->texture = resources_.GetTexture(Texture::PLAYER_WALKING);
      sprite_->render_flip = SDL_FLIP_NONE;
      num_frames_ = 4;
    } else if(factor < 0) {
      sprite_->texture = resources_.GetTexture(Texture::PLAYER_WALKING);
      sprite_->render_flip = SDL_FLIP_HORIZONTAL;
      num_frames_ = 4;
    }
  }
}

void Player::Update(float seconds_elapsed) {
  current_frame_duration_ += seconds_elapsed;
  if(current_frame_duration_ >= 0.25) {

    current_frame_++;
    if(current_frame_ >= num_frames_) {
      current_frame_ = 0;
    }

    sprite_->src_rect.x = current_frame_ * 16;
    current_frame_duration_ = 0;
  }

  x_ += PLAYER_SPEED * velocityFactor_ * seconds_elapsed;
}
