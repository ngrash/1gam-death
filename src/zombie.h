#ifndef ZOMBIE_H_
#define ZOMBIE_H_

#include "character.h"
#include "player.h"
#include "resources.h"
#include "zombie_state.h"
#include "zombie_state_asleep.h"
#include "zombie_state_rising.h"
#include "zombie_state_chasing.h"

class Zombie : public Character {
  friend class ZombieStateAsleep;
  friend class ZombieStateRising;
  friend class ZombieStateChasing;

  public:
    Zombie(Resources& resources, Player& player);
    ~Zombie();
    void Update(float seconds_elapsed);
    void SetState(ZombieState* state);

    ZombieStateAsleep* state_asleep_;
    ZombieStateRising* state_rising_;
    ZombieStateChasing* state_chasing_;
  private:
    Player& player_;
    Resources& resources_;
    ZombieState* current_state_;
};

#endif // ZOMBIE_H_
