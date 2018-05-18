#ifndef ZOMBIE_H_
#define ZOMBIE_H_

#include "sprite.h"
#include "resources.h"

class Zombie {
  public:
    Zombie(Resources& resources);
    ~Zombie();
    Sprite* GetSprite();
    int GetX();
    int GetY();
    void Update(float seconds_elapsed);

  private:
    Sprite* sprite_;
    int x_;
    int y_;
};

#endif // ZOMBIE_H_
