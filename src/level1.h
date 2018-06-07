#ifndef LEVEL1_H_
#define LEVEL1_H_

#include <vector>
#include <string>

#include "level.h"
#include "resources.h"
#include "sprite.h"
#include "world.h"
#include "zombie.h"
#include "sound.h"

class Level1 : public Level {
  public:
    Level1(Resources& resources, Sound& sound);
    ~Level1();

    Texture GetBackgroundTexture();
    Texture GetIntroTexture();
    void Initialize(World& world);
    void Update(float seconds_elapsed, World& world, StateManager& state_manager);
  private:
    Resources& resources_;
    Sound& sound_;
    Zombie* first_zombie_;

    std::string* text_intro_;
    std::string* text_spotted_;
    std::string* text_wave_1_;
    std::string* text_undead_;
    std::string* text_locked_chapel_;
    std::string* text_gargoyle_;
    std::string* text_crypta_;

    bool spawned_first_zombie_;
    bool spawned_wave_1_;
    bool spawned_wave_2_;
    bool spawned_wave_3_;
    bool spawned_wave_4_;
    bool mentioned_undead_;
    bool mentioned_locked_chapel_;
    bool mentioned_gargoyle_;
    bool mentioned_crypta_;

    void SpawnWave1(World& world);
    void SpawnWave2(World& world);
    void SpawnWave3(World& world);
    void SpawnWave4(World& world);

    Zombie* SpawnZombie(World& world, int x);
};

#endif // LEVEL1_H_
