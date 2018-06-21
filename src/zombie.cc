#include "zombie.h"

#include <cmath>

Zombie::Zombie(World& world) :
  world_(world)
{
  health_ = 1;

  hitbox_.x = 3;
  hitbox_.y = 0;
  hitbox_.w = 10;
  hitbox_.h = 16;

  state_asleep_ = new ZombieStateAsleep();
  state_rising_ = new ZombieStateRising();
  state_chasing_ = new ZombieStateChasing();
  state_attacking_ = new ZombieStateAttacking();
  state_dying_ = new ZombieStateDying();
  state_dead_ = new ZombieStateDead();

  SetState(state_asleep_);
}

Zombie::~Zombie() {
  delete state_asleep_;
  delete state_rising_;
  delete state_chasing_;
  delete state_attacking_;
}

void Zombie::SetState(ZombieState* state) {
  current_state_ = state;
  current_state_->Initialize(*this);
}

void Zombie::Update(float seconds_elapsed) {
  if(health_ <= 0 && current_state_ != state_dying_ && current_state_ != state_dead_) {
    SetState(state_dying_);
  }

  current_state_->Update(seconds_elapsed, *this);
}

float Zombie::GetDistanceToPlayer() {
  Player& player = world_.GetPlayer();
  return abs(player.position_.x - player.position_.x);
}
