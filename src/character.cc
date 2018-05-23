#include "character.h"

Character::Character() {
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
