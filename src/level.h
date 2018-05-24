#ifndef LEVEL_H_
#define LEVEL_H_

#include "resources.h"
#include "world.h"

class Level {
  public:
    virtual ~Level() {}
    virtual Texture GetBackgroundTexture() = 0;
    virtual void Initialize(World& world) {}
    virtual void Update(float seconds_elapsed, World& world) = 0;
};

#endif // LEVEL_H_
