#include "collisions.h"

void Collisions::Clear() {
  collidables_.clear();
}

void Collisions::AddCollidable(Character* character) {
  collidables_.push_back(character);
}

bool Collisions::DoesCollide(Character* character) {
  SDL_Rect chb;
  chb.x = character->hitbox_.x + character->position_.x;
  chb.y = character->hitbox_.y + character->position_.y;
  chb.w = character->hitbox_.w;
  chb.h = character->hitbox_.h;

  SDL_Rect ohb;
  for(int i = 0; i < collidables_.size(); i++) {
    Character* other = collidables_[i];

    ohb.x = other->hitbox_.x + other->position_.x;
    ohb.y = other->hitbox_.y + other->position_.y;
    ohb.w = other->hitbox_.w;
    ohb.h = other->hitbox_.h;

    if(DoOverlap(chb, ohb)) {
      return true;
    }
  }

  return false;
}

bool Collisions::DoCollide(Character* character, Character* other) {
  SDL_Rect chb;
  chb.x = character->hitbox_.x + character->position_.x;
  chb.y = character->hitbox_.y + character->position_.y;
  chb.w = character->hitbox_.w;
  chb.h = character->hitbox_.h;

  SDL_Rect ohb;
  ohb.x = other->hitbox_.x + other->position_.x;
  ohb.y = other->hitbox_.y + other->position_.y;
  ohb.w = other->hitbox_.w;
  ohb.h = other->hitbox_.h;

  return DoOverlap(chb, ohb);
}

bool Collisions::DoOverlap(SDL_Rect r1, SDL_Rect r2) {
  // https://stackoverflow.com/a/306332/159036

  int ax1 = r1.x;
  int ay1 = r1.y + r1.h;
  int ax2 = r1.x + r1.w;
  int ay2 = r1.y;
  int bx1 = r2.x;
  int by1 = r2.y + r2.h;
  int bx2 = r2.x + r2.w;
  int by2 = r2.y;

  return ax1 <= bx2 && ax2 >= bx1 && ay1 >= by2 && ay2 <= by1;
}
