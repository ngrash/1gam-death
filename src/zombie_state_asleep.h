#ifndef ZOMBIE_STATE_ASLEEP_H_
#define ZOMBIE_STATE_ASLEEP_H_

#include "zombie_state.h"

class ZombieStateAsleep : public ZombieState {
  public:
    void Initialize(Zombie& zombie);
    void Update(float seconds_elapsed, Zombie& zombie);
};

#endif // ZOMBIE_STATE_ASLEEP_H_
