#ifndef LEVEL1_H_
#define LEVEL1_H_

#include <vector>

#include "level.h"
#include "resources.h"
#include "sprite.h"
#include "world.h"
#include "zombie.h"

class Level1 : public Level {
  public:
    Level1(Resources& resources);;
    ~Level1();

    Texture GetBackgroundTexture();
    void Initialize(World& world);
    void Update(float seconds_elapsed, World& world);
  private:
    Resources& resources_;
    Zombie* first_zombie_;
};

#endif // LEVEL1_H_
