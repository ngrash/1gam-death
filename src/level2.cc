#include "level2.h"

#include "vector2f.h"
#include "credits_state.h"

Level2::Level2(Resources& resources, Sound& sound) :
  resources_(resources),
  sound_(sound),
  mentioned_intro_(false),
  spawned_first_bat_(false)
{
  text_intro_ = new std::string("This used to be a sacred place.");
}

Level2::~Level2() {
  delete text_intro_;
}

Texture Level2::GetBackgroundTexture() {
  return Texture::LEVEL_2;
}

Texture Level2::GetIntroTexture() {
  return Texture::LEVEL_2_INTRO;
}

int Level2::GetNumber() {
  return 2;
}

bool Level2::IsLevelOver() {
  return false;
}

void Level2::Initialize(World& world) {
  Player& player = world.GetPlayer();
  player.position_.x = world.level_width_ - 60;
  player.GetSprite()->render_flip = SDL_FLIP_HORIZONTAL;

  sound_.PlayMusic(Music::LEVEL_2_LOOP);

  first_bat_ = SpawnBat(world, world.level_width_ - 158);
}

void Level2::Update(float seconds_elapsed, World& world, StateManager& state_manager) {
  Player& player = world.GetPlayer();
  Vector2f player_pos = player.position_;

  if(!mentioned_intro_) {
    mentioned_intro_ = true;
    player.Say(text_intro_, 3);
  }

  if(!spawned_first_bat_ && player_pos.x <= world.level_width_ - 100) {
    spawned_first_bat_ = true;
    first_bat_->SetState(first_bat_->state_starting_);
  }

  if(player_pos.x >= 24 && player_pos.x <= 35 && player_pos.y <= 101) {
    state_manager.PushState(new CreditsState(resources_));
  }
}

Bat* Level2::SpawnBat(World& world, int x) {
  Bat* bat = new Bat(resources_, world.GetPlayer());
  bat->position_.x = x - 8;
  bat->position_.y = 67;
  world.Spawn(*bat);

  return bat;
}
