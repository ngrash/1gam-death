#ifndef BAT_STATE_FLYING_H_
#define BAT_STATE_FLYING_H_

#include "bat_state.h"

class BatStateFlying : public BatState {
  public:
    void Initialize(Bat& bat);
    void Update(float seconds_elapsed, Bat& bat);
};

#endif // BAT_STATE_FLYING_H_
