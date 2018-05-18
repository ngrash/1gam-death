#ifndef GAME_H_
#define GAME_H_

#include "resources.h"
#include "graphics.h"
#include "player.h"
#include "zombie.h"

class Game {
  public:
    Game();
    bool Init();
    void Run();
    void Quit();

  private:
    Resources* resources_;
    Graphics* graphics_;
    SDL_Renderer* renderer_;
    SDL_Window* window_;
    bool loop_;

    Player* player_;
    Zombie* zombie_;
    int playerVelocityX_;

    void HandleInput();
    void Update(float seconds_elapsed);
    void Render(Graphics& graphics);
};

#endif // GAME_H_
