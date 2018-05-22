#ifndef ZOMBIE_STATE_ASLEEP
#define ZOMBIE_STATE_ASLEEP

#include "zombie_state.h"

class ZombieStateAsleep : public ZombieState {
  public:
    void Initialize(Zombie& zombie);
    void Update(float seconds_elapsed, Zombie& zombie);
};

#endif
