#ifndef LEVEL2_H_
#define LEVEL2_H_

#include <vector>
#include <string>

#include "level.h"
#include "resources.h"
#include "sound.h"
#include "sprite.h"
#include "world.h"
#include "zombie.h"

class Level2 : public Level {
  public:
    Level2(Resources& resources, Sound& sound);
    ~Level2();

    Texture GetBackgroundTexture();
    Texture GetIntroTexture();
    void Initialize(World& world);
    void Update(float seconds_elapsed, World& world, StateManager& state_manager);
    int GetNumber();
    bool IsLevelOver();
  private:
    Resources& resources_;
    Sound& sound_;

    std::string* text_intro_;
};

#endif // LEVEL2_H_
