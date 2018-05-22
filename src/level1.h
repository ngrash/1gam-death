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

    bool spawned_first_zombie_;
    bool spawned_wave_1_;
    bool spawned_wave_2_;

    void SpawnWave1(World& world);
    void SpawnWave2(World& world);

    void SpawnZombie(World& world, int x);
};

#endif // LEVEL1_H_
