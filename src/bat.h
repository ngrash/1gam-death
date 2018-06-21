#ifndef BAT_H_
#define BAT_H_

#include "player.h"
#include "character.h"
#include "resources.h"
#include "bat_state.h"
#include "bat_state_asleep.h"
#include "bat_state_flying.h"
#include "bat_state_starting.h"
#include "bat_state_attacking.h"

class Bat : public Character {
  friend class BatStateAsleep;
  friend class BatStateFlying;
  friend class BatStateStarting;
  friend class BatStateAttacking;

  public:
    Bat(Resources& resources, Player& player);
    ~Bat();
    void Update(float seconds_elapsed);
    void SetState(BatState* state);

    BatStateAsleep* state_asleep_;
    BatStateFlying* state_flying_;
    BatStateStarting* state_starting_;
    BatStateAttacking* state_attacking_;
  private:
    BatState* current_state_;
    Resources& resources_;
    Player& player_;
};

#endif // BAT_H_
