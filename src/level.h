#ifndef LEVEL_H_
#define LEVEL_H_

#include "state_manager.h"
#include "world.h"

class Level {
  public:
    virtual ~Level() {}
    virtual Texture GetBackgroundTexture() = 0;
    virtual Texture GetIntroTexture() = 0;
    virtual void Initialize(World& world) {}
    virtual void Update(float seconds_elapsed, World& world, StateManager& state_manager) = 0;
    virtual int GetNumber() = 0;
    virtual bool IsLevelOver() = 0;
};

#endif // LEVEL_H_
