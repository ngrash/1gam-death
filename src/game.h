#ifndef GAME_H_
#define GAME_H_

#include "character.h"
#include "graphics.h"
#include "player.h"
#include "resources.h"
#include "vector2f.h"
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
    Sprite* level_;
    int level_width_;
    Vector2f camera_;

    void HandleInput();
    void Update(float seconds_elapsed);
    void Render(Graphics& graphics);

    void RenderCharacter(Graphics& g, Character& character, Vector2f camera);
    void RenderSprite(Graphics& g, Sprite* sprite, Vector2f position, Vector2f camera);
};

#endif // GAME_H_
