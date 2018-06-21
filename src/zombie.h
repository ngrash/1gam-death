#ifndef ZOMBIE_H_
#define ZOMBIE_H_

#include "character.h"
#include "world.h"
#include "zombie_state.h"
#include "zombie_state_asleep.h"
#include "zombie_state_attacking.h"
#include "zombie_state_chasing.h"
#include "zombie_state_dead.h"
#include "zombie_state_dying.h"
#include "zombie_state_rising.h"

class Zombie : public Character {
  friend class ZombieStateAsleep;
  friend class ZombieStateRising;
  friend class ZombieStateChasing;
  friend class ZombieStateAttacking;
  friend class ZombieStateDying;
  friend class ZombieStateDead;

  public:
    Zombie(World& world);
    ~Zombie();
    void Update(float seconds_elapsed);
    void SetState(ZombieState* state);
    float GetDistanceToPlayer();

    ZombieStateAsleep* state_asleep_;
    ZombieStateRising* state_rising_;
    ZombieStateChasing* state_chasing_;
    ZombieStateAttacking* state_attacking_;
    ZombieStateDying* state_dying_;
    ZombieStateDead* state_dead_;
  private:
    World& world_;
    ZombieState* current_state_;
};

#endif // ZOMBIE_H_
