#ifndef PLAYER_H_
#define PLAYER_H_

#include "sprite.h"
#include "resources.h"

class Player {
  public:
    Player(Resources& resources);
    ~Player();
    Sprite* GetSprite();
    void Update(float seconds_elapsed);
    float x_;
    float y_;
    void SetVelocity(float factor);

  private:
    Resources& resources_;
    Sprite* sprite_;
    int num_frames_;
    int current_frame_;
    float current_frame_duration_;
    float velocityFactor_;
};

#endif // PLAYER_H_
