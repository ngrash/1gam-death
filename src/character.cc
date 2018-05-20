#include "character.h"

Character::Character() {
  animation_ = new Animation();
}

Character::~Character() {
  delete animation_;
}

Sprite* Character::GetSprite() {
  return animation_;
}

Vector2f Character::GetPosition() {
  return position_;
}
