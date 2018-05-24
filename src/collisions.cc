#include "collisions.h"

#include <cmath>

#include "logging.h"

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

Character* Collisions::GetCharacterInLine(int x, int y, int direction, int max_distance) {
  Character* nearest = nullptr;

  for(int i = 0; i < collidables_.size(); i++) {
    Character* other = collidables_[i];

    SDL_Rect hitbox;
    hitbox.x = other->hitbox_.x + other->position_.x;
    hitbox.y = other->hitbox_.y + other->position_.y;
    hitbox.w = other->hitbox_.w;
    hitbox.h = other->hitbox_.h;

    int distance_to_player = abs(x - other->position_.x);

    if(distance_to_player <= max_distance && y <= (hitbox.y + hitbox.h) && y >= hitbox.y) {
      // right
      if(direction > 0 && other->position_.x >= x) {
        if(nearest == nullptr || other->position_.x < nearest->position_.x) {
          nearest = other;
        }
      }
      // left
      else if(direction < 0 && other->position_.x <= x) {
        if(nearest == nullptr || other->position_.x > nearest->position_.x) {
          nearest = other;
        }
      }
    }
  }


  return nearest;
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
