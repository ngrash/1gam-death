#ifndef ZOMBIE_STATE_ATTACKING_H_
#define ZOMBIE_STATE_ATTACKING_H_

#include "zombie_state.h"

class ZombieStateAttacking : public ZombieState {
  public:
    void Initialize(Zombie& zombie);
    void Update(float seconds_elapsed, Zombie& zombie);
  private:
    float state_duration_;
};

#endif // ZOMBIE_STATE_ATTACKING_H_
