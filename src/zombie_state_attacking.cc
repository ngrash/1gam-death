#include "zombie_state_attacking.h"

#include "zombie.h"

#define ATTACK_RANGE 14
#define ATTACK_HEIGHT 16

void ZombieStateAttacking::Initialize(Zombie& zombie) {
  state_duration_ = 0;
  dealt_damage_ = false;
  zombie.animation_->Reset();
  zombie.animation_->texture = zombie.world_.GetResources().GetTexture(Texture::ZOMBIE_ATTACKING);
  zombie.animation_->frame_duration = 0.5;
  zombie.animation_->num_frames = 2;
}

void ZombieStateAttacking::Update(float seconds_elapsed, Zombie& zombie) {
  zombie.animation_->Update(seconds_elapsed);

  state_duration_ += seconds_elapsed;

  if(!dealt_damage_ && state_duration_ >= 0.5) {
    dealt_damage_ = true;

    Player& player = zombie.world_.GetPlayer();

    if(zombie.world_.GetDistanceToPlayer(&zombie) <= ATTACK_RANGE
       && player.position_.y <= ATTACK_HEIGHT) {
      player.health_ -= 1;
    }
  }

  if(state_duration_ >= 1) {
    zombie.SetState(zombie.state_chasing_);
  }
}
