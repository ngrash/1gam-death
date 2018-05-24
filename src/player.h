#ifndef PLAYER_H_
#define PLAYER_H_

#include "character.h"
#include "collisions.h"
#include "resources.h"
#include "vector2f.h"

class Player : public Character {
  public:
    Player(Resources& resources, Collisions& collisions);
    void Update(float seconds_elapsed);
    void SetVelocityXFactor(float factor);
    void Jump();
    void Shot();
    int health_;
    int shells_;
  private:
    Resources& resources_;
    Collisions& collisions_;

    float velocity_x_factor_;
};

#endif // PLAYER_H_
