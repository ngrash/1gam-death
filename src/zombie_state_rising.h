#ifndef ZOMBIE_STATE_RISING_H_
#define ZOMBIE_STATE_RISING_H_

#include "zombie_state.h"

class ZombieStateRising : public ZombieState {
  public:
    void Initialize(Zombie& zombie);
    void Update(float seconds_elapsed, Zombie& zombie);
  private:
    float state_duration_;
};

#endif // ZOMBIE_STATE_RISING_H_
