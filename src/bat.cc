#include "bat.h"

Bat::Bat(World& world) :
  world_(world)
{
  health_ = 1;

  hitbox_.x = 1;
  hitbox_.y = -5;
  hitbox_.w = 13;
  hitbox_.h = 7;

  state_asleep_ = new BatStateAsleep();
  state_flying_ = new BatStateFlying();
  state_starting_ = new BatStateStarting();
  state_attacking_ = new BatStateAttacking();

  SetState(state_asleep_);
}

Bat::~Bat() {
  delete state_asleep_;
  delete state_flying_;
  delete state_starting_;
  delete state_attacking_;
}

void Bat::SetState(BatState* state) {
  current_state_ = state;
  current_state_->Initialize(*this);
}

void Bat::Update(float seconds_elapsed) {
  current_state_->Update(seconds_elapsed, *this);
}

