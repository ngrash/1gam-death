#ifndef COLLISIONS_H_
#define COLLISIONS_H_

#include <vector>

#include <SDL2/SDL_rect.h>

#include "character.h"

class Collisions {
  public:
    void Clear();
    void AddCollidable(Character* character);
    bool DoesCollide(Character* character);
    bool DoCollide(Character* character, Character* other);
    Character* GetCharacterInLine(int x, int y, int direction, int max_distance);
  private:
    std::vector<Character*> collidables_;

    bool DoOverlap(SDL_Rect r1, SDL_Rect r2);
};

#endif // COLLISIONS_H_
