#include "character.h"

Character::Character() {
  health_ = 0;
  animation_ = new Animation();
  acceleration_ = {};
  velocity_ = {};
  position_ = {};
}

Character::~Character() {
  delete animation_;
}

Sprite* Character::GetSprite() {
  return animation_;
}
