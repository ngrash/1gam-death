#include "level1.h"
#include "vector2f.h"

Level1::Level1(Resources& resources) :
  resources_(resources),
  spawned_first_zombie_(false),
  spawned_wave_1_(false),
  spawned_wave_2_(false)
{}

Level1::~Level1() {
  if(first_zombie_ != nullptr) {
    delete first_zombie_;
  }
}

Texture Level1::GetBackgroundTexture() {
  return Texture::LEVEL_1;
}

void Level1::Initialize(World& world) {
  Player* player = world.GetPlayer();
  player->position_.x = 16;
  player->position_.y = 16;
}

void Level1::Update(float seconds_elapsed, World& world) {
  Vector2f player_pos = world.GetPlayer()->position_;

  if(!spawned_first_zombie_ && player_pos.x >= 299 - 8) {
    spawned_first_zombie_ = true;
    // TODO: Say "What's this on the other side of the street? I'll better get prepared."
    SpawnZombie(world, 580);
  }

  if(!spawned_wave_1_ && player_pos.x >= 647 - 8) {
    // TODO: Say "For hell's sake. The deads are after me."
    spawned_wave_1_ = true;
    SpawnWave1(world);
  }

  if(!spawned_wave_2_ && player_pos.x >= 770 - 8) {
    spawned_wave_2_ = true;
    SpawnWave2(world);
  }
}

void Level1::SpawnWave1(World& world) {
  SpawnZombie(world, 598);
  SpawnZombie(world, 615);
  SpawnZombie(world, 696);
  SpawnZombie(world, 727);
}

void Level1::SpawnWave2(World& world) {
  SpawnZombie(world, 711);
  SpawnZombie(world, 744);
  SpawnZombie(world, 807);
  SpawnZombie(world, 839);
  SpawnZombie(world, 871);
}

void Level1::SpawnZombie(World& world, int x) {
  Zombie* z = new Zombie(resources_, *world.GetPlayer());
  z->SetState(z->state_rising_);
  z->position_.x = x - 8;
  z->position_.y = 16;
  world.Spawn(*z);
}
