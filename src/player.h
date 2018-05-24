#ifndef PLAYER_H_
#define PLAYER_H_

#include <string>

#include "character.h"
#include "collisions.h"
#include "resources.h"
#include "vector2f.h"

class Player : public Character {
  public:
    Player(Resources& resources, Collisions& collisions);
    ~Player();
    void Update(float seconds_elapsed);
    void SetVelocityXFactor(float factor);
    void Jump();
    void Shot();
    void Say(std::string* text, float display_duration);;

    int health_;
    int shells_;
    bool reloading_;
    Animation* reloading_animation_;
    std::string* text_;
    bool has_text_;
  private:
    Resources& resources_;
    Collisions& collisions_;
    float velocity_x_factor_;
    float reload_duration_;
    float text_display_duration_target_;
    float text_display_duration_;;
};

#endif // PLAYER_H_
