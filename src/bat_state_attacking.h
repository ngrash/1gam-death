#ifndef BAT_STATE_ATTACKING_H_
#define BAT_STATE_ATTACKING_H_

#include "bat_state.h"

class BatStateAttacking : public BatState {
  public:
    void Initialize(Bat& bat);
    void Update(float seconds_elapsed, Bat& bat);
  private:
    float state_duration_;
    bool dealt_damage_;
};

#endif // BAT_STATE_ATTACKING_H_
