#ifndef BAT_H_
#define BAT_H_

#include "bat_state.h"
#include "bat_state_asleep.h"
#include "bat_state_attacking.h"
#include "bat_state_flying.h"
#include "bat_state_starting.h"
#include "character.h"
#include "world.h"

class Bat : public Character {
  friend class BatStateAsleep;
  friend class BatStateFlying;
  friend class BatStateStarting;
  friend class BatStateAttacking;

  public:
    Bat(World& world);
    ~Bat();
    void Update(float seconds_elapsed);
    void SetState(BatState* state);

    BatStateAsleep* state_asleep_;
    BatStateFlying* state_flying_;
    BatStateStarting* state_starting_;
    BatStateAttacking* state_attacking_;
  private:
    World& world_;
    BatState* current_state_;
};

#endif // BAT_H_
