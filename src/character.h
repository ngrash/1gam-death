#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "animation.h"
#include "sprite.h"
#include "vector2f.h"

class Character {
  public:
    Character();
    ~Character();
    Sprite* GetSprite();
    virtual void Update(float seconds_elapsed) = 0;
    Vector2f GetPosition();
  protected:
    Animation* animation_;
    Vector2f position_;
    Vector2f acceleration_;
    Vector2f velocity_;
};

#endif // CHARACTER_H_
