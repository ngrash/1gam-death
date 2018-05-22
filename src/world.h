#ifndef WORLD_H_
#define WORLD_H_

#include <vector>

#include "character.h"
#include "player.h"

class World {
  public:
    World(Player& player);
    Player* GetPlayer();
    void Spawn(Character& character);
    void Release();
    void Update(float seconds_elapsed);
    std::vector<Character*>* GetCharacters();
  private:
    Player* player_;
    std::vector<Character*> characters_;
};

#endif // WORLD_H_
