#include "world.h"

World::World(Player& player, Collisions& collisions) :
  player_(player),
  collisions_(collisions)
{}

void World::Update(float seconds_elapsed) {
  for(std::vector<Character*>::size_type i = 0; i < characters_.size(); i++) {
    characters_[i]->Update(seconds_elapsed);
  }
}

Player* World::GetPlayer() {
  return &player_;
}

std::vector<Character*>* World::GetCharacters() {
  return &characters_;
}

void World::Spawn(Character& character) {
  characters_.push_back(&character);
  collisions_.AddCollidable(&character);
}

void World::Release() {
  for(std::vector<Character*>::size_type i = 0; i < characters_.size(); i++) {
    delete characters_[i];
  }

  characters_.clear();
  collisions_.Clear();
}

