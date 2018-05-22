#ifndef ZOMBIE_H_
#define ZOMBIE_H_

#include "character.h"
#include "player.h"
#include "resources.h"

class Zombie : public Character {
  public:
    Zombie(Resources& resources, Player& player);
    void Update(float seconds_elapsed);
  private:
    Player& player_;
    Resources& resources_;
};

#endif // ZOMBIE_H_
