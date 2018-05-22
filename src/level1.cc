#include "level1.h"

Level1::Level1(Resources& resources)
  : resources_(resources)
{}

Level1::~Level1() {
  delete first_zombie_;
}

Texture Level1::GetBackgroundTexture() {
  return Texture::LEVEL_1;
}

void Level1::Initialize(World& world) {
  first_zombie_ = new Zombie(resources_, *world.GetPlayer());
  world.Spawn(*first_zombie_);
}

void Level1::Update(float seconds_elapsed, World& world) {
  // TODO: Check player position and wake zombies
}
