#ifndef WORLD_H_
#define WORLD_H_

#include <vector>

#include "collisions.h"
#include "character.h"
#include "player.h"

class World {
  public:
    World(Player& player, Collisions& collisions);
    Player* GetPlayer();
    void Spawn(Character& character);
    void Release();
    void Update(float seconds_elapsed);
    std::vector<Character*>* GetCharacters();
  private:
    Player& player_;
    Collisions& collisions_;
    std::vector<Character*> characters_;
};

#endif // WORLD_H_
