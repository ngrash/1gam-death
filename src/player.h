#ifndef PLAYER_H_
#define PLAYER_H_

#include "character.h"
#include "resources.h"

class Player : public Character {
  public:
    Player(Resources& resources);
    void Update(float seconds_elapsed);
    void SetVelocity(float factor);

  private:
    Resources& resources_;
    float velocityFactor_;
};

#endif // PLAYER_H_
