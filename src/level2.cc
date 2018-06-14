#include "level2.h"

#include "vector2f.h"
#include "credits_state.h"

Level2::Level2(Resources& resources, Sound& sound) :
  resources_(resources),
  sound_(sound)
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
  Player* player = world.GetPlayer();
  player->position_.x = world.level_width_ - 60;
  player->GetSprite()->render_flip = SDL_FLIP_HORIZONTAL;

  sound_.PlayMusic(Music::LEVEL_2_LOOP);
}

void Level2::Update(float seconds_elapsed, World& world, StateManager& state_manager) {
  Vector2f player_pos = world.GetPlayer()->position_;
  if(player_pos.x >= 24 && player_pos.x <= 35 && player_pos.y <= 101) {
    state_manager.PushState(new CreditsState(resources_));
  }
}

