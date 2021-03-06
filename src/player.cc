#include "player.h"

#include "world.h"

#define MAX_PLAYER_VELOCITY_X 50
#define MAX_PLAYER_VELOCITY_Y 50
#define FLOOR_Y 16

#define WEAPON_RELOAD_TIME_S 2
#define WEAPON_DISTANCE 80
#define WEAPON_Y 9

Player::Player(World& world) :
  health_(3),
  shells_(0),
  score_(0),
  reloading_(false),
  unarmed_(false),
  text_(nullptr),
  has_text_(false),
  world_(world),
  velocity_x_factor_(0),
  reload_duration_(0),
  text_display_duration_target_(0),
  text_display_duration_(0)
{
  hitbox_.x = 5;
  hitbox_.y = 0;
  hitbox_.h = 16;
  hitbox_.w = 5;

  animation_->frame_duration = 0.10f;
  animation_->texture = world_.GetResources().GetTexture(Texture::PLAYER_IDLE);

  reloading_animation_ = new Animation();
  reloading_animation_->texture = world_.GetResources().GetTexture(Texture::RELOADING);
  reloading_animation_->src_rect.w = 32;
  reloading_animation_->num_frames = 33;
  reloading_animation_->frame_duration = WEAPON_RELOAD_TIME_S / (float)reloading_animation_->num_frames;
}

Player::~Player() {
  delete reloading_animation_;
}

void Player::SetVelocityXFactor(float factor) {
  if(world_.GetCollisions().DoesCollide(this)) {
    if(factor > 0) {
      factor = 0.5;
    } else if(factor < 0) {
      factor = -0.5;
    }
  }

  if(velocity_x_factor_ != factor) {
    velocity_x_factor_ = factor;

    velocity_.x = MAX_PLAYER_VELOCITY_X * factor;

    animation_->Reset();
  }

  if(factor == 0) {
    Texture idle_texture = unarmed_ ? Texture::PLAYER_IDLE : Texture::PLAYER_IDLE_W_SHOTGUN;
    animation_->texture = world_.GetResources().GetTexture(idle_texture);
    animation_->num_frames = 0;
  }
  else {
    Texture walking_texture = unarmed_ ? Texture::PLAYER_WALKING : Texture::PLAYER_WALKING_W_SHOTGUN;

    if(factor > 0) {
      animation_->texture = world_.GetResources().GetTexture(walking_texture);
      animation_->render_flip = SDL_FLIP_NONE;
      animation_->num_frames = 4;
    } else if(factor < 0) {
      animation_->texture = world_.GetResources().GetTexture(walking_texture);
      animation_->render_flip = SDL_FLIP_HORIZONTAL;
      animation_->num_frames = 4;
    }
  }
}

void Player::Jump() {
  if(position_.y == FLOOR_Y) {
    velocity_.y = 200;
    acceleration_.y = -700;
  }
}

void Player::Shot() {
  if(reloading_) {
    return;
  }

  int direction = animation_->render_flip == SDL_FLIP_NONE ? 1 : -1;
  Character* enemy = world_.GetCollisions().GetCharacterInLine((int)position_.x, (int)position_.y + WEAPON_Y, direction, WEAPON_DISTANCE);

  if(enemy != nullptr) {
    enemy->health_--;
    if(enemy->health_ <= 0) {
      score_ += 100;
    }
  }

  shells_--;
}

void Player::Say(std::string* text, float display_duration) {
  has_text_ = text != nullptr;
  text_ = text;
  text_display_duration_target_ = display_duration;
  text_display_duration_ = 0;
}

void Player::Update(float seconds_elapsed) {
  animation_->Update(seconds_elapsed);

  if(shells_ <= 0 && !reloading_ && !unarmed_) {
    reloading_ = true;
    reload_duration_ = 0;
    reloading_animation_->Reset();
  }

  if(reloading_) {
    reloading_animation_->Update(seconds_elapsed);
    reload_duration_ += seconds_elapsed;
    if(reload_duration_ >= WEAPON_RELOAD_TIME_S) {
      reloading_ = false;
      shells_ = 3;
    }
  }

  if(has_text_) {
    text_display_duration_ += seconds_elapsed;
    if(text_display_duration_ >= text_display_duration_target_) {
      Say(nullptr, 0);
    }
  }

  velocity_.x += acceleration_.x * seconds_elapsed;
  velocity_.y += acceleration_.y * seconds_elapsed;

  position_.x += velocity_.x * seconds_elapsed;
  position_.y += velocity_.y * seconds_elapsed;

  if(position_.y < FLOOR_Y) {
    position_.y = FLOOR_Y;
    velocity_.y = 0;
    acceleration_.y = 0;
  }
}
