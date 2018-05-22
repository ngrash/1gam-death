#include "world.h"

World::World(Player& player) {
  player_ = &player;
}

void World::Update(float seconds_elapsed) {
  for(int i = 0; i < characters_.size(); i++) {
    characters_[i]->Update(seconds_elapsed);
  }
}

Player* World::GetPlayer() {
  return player_;
}

std::vector<Character*>* World::GetCharacters() {
  return &characters_;
}

void World::Spawn(Character& character) {
    characters_.push_back(&character);
}

void World::Release() {
  // whoever spawned those characters better cleans them up
  // the world just forgets about them
  characters_.clear();
}

