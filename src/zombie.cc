#include "zombie.h"

#include <cmath>

Zombie::Zombie(Resources& resources, Player& player) :
  player_(player),
  resources_(resources)
{
  hitbox_.x = 3;
  hitbox_.y = 0;
  hitbox_.w = 10;
  hitbox_.h = 16;

  state_asleep_ = new ZombieStateAsleep();
  state_rising_ = new ZombieStateRising();
  state_chasing_ = new ZombieStateChasing();
  state_attacking_ = new ZombieStateAttacking();

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
  current_state_->Update(seconds_elapsed, *this);
}

float Zombie::GetDistanceToPlayer() {
  return abs(player_.position_.x - position_.x);
}
