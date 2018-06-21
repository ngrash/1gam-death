#ifndef WORLD_H_
#define WORLD_H_

#include <vector>

#include "collisions.h"
#include "character.h"
#include "player.h"

class World {
  public:
    World(Player& player, Collisions& collisions, Resources& resources);

    void Spawn(Character& character);
    void Release();
    void Update(float seconds_elapsed);

    int level_width_;

    std::vector<Character*>* GetCharacters();
    Player& GetPlayer();
    Collisions& GetCollisions();
    Resources& GetResources();
  private:
    Player& player_;
    Collisions& collisions_;
    Resources& resources_;
    std::vector<Character*> characters_;
};

#endif // WORLD_H_
