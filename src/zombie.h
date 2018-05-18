#ifndef ZOMBIE_H_
#define ZOMBIE_H_

#include "character.h"
#include "resources.h"
#include "sprite.h"

class Zombie : public Character {
  public:
    Zombie(Resources& resources);
    void Update(float seconds_elapsed);
};

#endif // ZOMBIE_H_
