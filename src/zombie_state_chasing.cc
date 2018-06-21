#include "zombie_state_chasing.h"

#include "vector2f.h"
#include "zombie.h"

#define DESIRED_DISTANCE_TO_PLAYER 10
#define MAX_ZOMBIE_VELOCITY_X 10

void ZombieStateChasing::Initialize(Zombie& zombie) {
  zombie.animation_->Reset();
  zombie.animation_->texture = zombie.world_.GetResources().GetTexture(Texture::ZOMBIE_WALKING);
  zombie.animation_->frame_duration = 0.25;
  zombie.animation_->num_frames = 0;
}

void ZombieStateChasing::Update(float seconds_elapsed, Zombie& zombie) {
  zombie.animation_->Update(seconds_elapsed);

  Vector2f player_pos = zombie.world_.GetPlayer().position_;

  if(player_pos.x > zombie.position_.x) {
    zombie.animation_->render_flip = SDL_FLIP_NONE;
    zombie.velocity_.x = MAX_ZOMBIE_VELOCITY_X;
  }
  else if(player_pos.y < zombie.position_.x) {
    zombie.animation_->render_flip = SDL_FLIP_HORIZONTAL;
    zombie.velocity_.x = -MAX_ZOMBIE_VELOCITY_X;
  }

  float distance_to_player = zombie.GetDistanceToPlayer();
  bool reached_player = distance_to_player <= DESIRED_DISTANCE_TO_PLAYER;

  if(reached_player) {
    zombie.SetState(zombie.state_attacking_);
  } else {
    zombie.animation_->texture = zombie.world_.GetResources().GetTexture(Texture::ZOMBIE_WALKING);
    zombie.animation_->num_frames = 4;

    zombie.position_.x += zombie.velocity_.x * seconds_elapsed;
  }
}
