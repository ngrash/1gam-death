#ifndef CHARACTER_H_
#define CHARACTER_H_

#include <SDL2/SDL_rect.h>

#include "animation.h"
#include "sprite.h"
#include "vector2f.h"

class Character {
  public:
    Character();
    virtual ~Character();
    Sprite* GetSprite();
    virtual void Update(float seconds_elapsed) = 0;
    Vector2f position_;
    SDL_Rect hitbox_;
    int health_;
  protected:
    Animation* animation_;
    Vector2f acceleration_;
    Vector2f velocity_;
};

#endif // CHARACTER_H_
