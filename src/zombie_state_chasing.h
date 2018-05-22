#ifndef ZOMBIE_STATE_CHASING_H_
#define ZOMBIE_STATE_CHASING_H_

#include "zombie_state.h"

class ZombieStateChasing : public ZombieState {
  public:
    void Initialize(Zombie& zombie);
    void Update(float seconds_elapsed, Zombie& zombie);
};

#endif // ZOMBIE_STATE_CHASING_H_
