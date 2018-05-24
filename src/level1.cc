#include "level1.h"
#include "vector2f.h"

Level1::Level1(Resources& resources) :
  resources_(resources),
  first_zombie_(nullptr),
  spawned_first_zombie_(false),
  spawned_wave_1_(false),
  spawned_wave_2_(false),
  mentioned_undead_(false),
  mentioned_locked_chapel_(false)
{
  text_intro_ = new std::string("I've come to purge this place.");
  text_spotted_ = new std::string("What's moving over there?");
  text_wave_1_ = new std::string("For hell's sake!");
  text_undead_ = new std::string("Undead!");
  text_locked_chapel_ = new std::string("The chapel is locked.");
}

Level1::~Level1() {
  delete text_intro_;
  delete text_spotted_;
  delete text_wave_1_;
  delete text_undead_;
  delete text_locked_chapel_;
}

Texture Level1::GetBackgroundTexture() {
  return Texture::LEVEL_1;
}

void Level1::Initialize(World& world) {
  Player* player = world.GetPlayer();
  player->position_.x = 16;
  player->position_.y = 16;

  player->Say(text_intro_, 5);
  world.GetPlayer()->unarmed_ = true;
}

void Level1::Update(float seconds_elapsed, World& world) {
  Vector2f player_pos = world.GetPlayer()->position_;
  Player* player = world.GetPlayer();

  if(!spawned_first_zombie_ && player_pos.x >= 299 - 8) {
    spawned_first_zombie_ = true;
    player->Say(text_spotted_, 3);
    player->unarmed_ = false;
    first_zombie_ = SpawnZombie(world, 580);
  }

  if(!mentioned_undead_ && first_zombie_ != nullptr
      && first_zombie_->position_.x - player->position_.x <= 70) {
    mentioned_undead_ = true;
    player->Say(text_undead_, 3);
  }

  if(!spawned_wave_1_ && player_pos.x >= 647 - 8) {
    spawned_wave_1_ = true;
    player->Say(text_wave_1_, 3);
    SpawnWave1(world);
  }

  if(!spawned_wave_2_ && player_pos.x >= 770 - 8) {
    spawned_wave_2_ = true;
    SpawnWave2(world);
  }

  if(!mentioned_locked_chapel_ && player_pos.x >= 978 - 8) {
    mentioned_locked_chapel_ = true;
    player->Say(text_locked_chapel_, 3);
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

Zombie* Level1::SpawnZombie(World& world, int x) {
  Zombie* z = new Zombie(resources_, *world.GetPlayer());
  z->SetState(z->state_rising_);
  z->position_.x = x - 8;
  z->position_.y = 16;
  world.Spawn(*z);

  return z;
}
