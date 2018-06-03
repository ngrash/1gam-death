#ifndef GAME_H_
#define GAME_H_

#include "graphics.h"
#include "resources.h"
#include "state_manager.h"

class Game {
  public:
    Game();
    bool Init();
    void Run();
    void Quit();

  private:
    Resources* resources_;
    Graphics* graphics_;
    StateManager* state_manager_;
    SDL_Renderer* renderer_;
    SDL_Window* window_;
    bool loop_;

    void HandleInput();
    void Update(float seconds_elapsed);
    void Render(Graphics& graphics);
};

#endif // GAME_H_
