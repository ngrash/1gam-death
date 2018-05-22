#ifndef PLAYER_H_
#define PLAYER_H_

#include "character.h"
#include "resources.h"
#include "vector2f.h"

class Player : public Character {
  public:
    Player(Resources& resources);
    void Update(float seconds_elapsed);
    void SetVelocityXFactor(float factor);
    void Jump();
    int health_;
  private:
    Resources& resources_;

    float velocity_x_factor_;
};

#endif // PLAYER_H_
