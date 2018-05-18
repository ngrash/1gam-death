#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "animation.h"
#include "sprite.h"

class Character {
  public:
    Character();
    ~Character();
    Sprite* GetSprite();
    virtual void Update(float seconds_elapsed) = 0;
    float GetX();
    float GetY();
  protected:
    Animation* animation_;
    float x_;
    float y_;
};

#endif // CHARACTER_H_
