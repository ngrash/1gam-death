#ifndef BAT_STATE_STARTING_H_
#define BAT_STATE_STARTING_H_

#include "bat_state.h"

class BatStateStarting : public BatState {
  public:
    void Initialize(Bat& bat);
    void Update(float seconds_elapsed, Bat& bat);
  private:
    float state_duration_;
};

#endif // BAT_STATE_STARTING_H_
