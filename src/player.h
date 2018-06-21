#ifndef PLAYER_H_
#define PLAYER_H_

#include <string>

#include "character.h"
#include "collisions.h"
#include "resources.h"
#include "vector2f.h"

class World;

class Player : public Character {
  public:
    Player(World& world);
    ~Player();
    void Update(float seconds_elapsed);
    void SetVelocityXFactor(float factor);
    void Jump();
    void Shot();
    void Say(std::string* text, float display_duration);;

    int health_;
    int shells_;
    int score_;
    bool reloading_;
    bool unarmed_;
    Animation* reloading_animation_;
    std::string* text_;
    bool has_text_;
  private:
    World& world_;
    float velocity_x_factor_;
    float reload_duration_;
    float text_display_duration_target_;
    float text_display_duration_;
};

#endif // PLAYER_H_
