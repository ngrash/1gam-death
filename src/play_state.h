#ifndef PLAY_STATE_H_
#define PLAY_STATE_H_

#include "SDL2/SDL.h"

#include "animation.h"
#include "character.h"
#include "collisions.h"
#include "graphics.h"
#include "level.h"
#include "player.h"
#include "sound.h"
#include "state.h"
#include "vector2f.h"

class PlayState : public State {
  public:
    PlayState(Resources& resources, Sound& sound, int screen_width, int screen_height);
    ~PlayState();
    void Initialize(StateManager& state_manager);
    void Update(StateManager& state_manager, float seconds_elapsed);
    void Draw(Graphics& graphics);
    void HandleEvent(StateManager& state_manager, SDL_Event& event);

  private:
    Resources& resources_;
    Sound& sound_;
    int screen_width_;
    int screen_height_;

    Player* player_;
    World* world_;
    Collisions* collisions_;

    int player_velocity_x_;
    Vector2f camera_;

    Level*  level_;
    Sprite* level_background_;
    int     level_width_;

    void RenderCharacter(Graphics& g, Character& character, Vector2f camera);
    void RenderSprite(Graphics& g, Sprite* sprite, Vector2f position, Vector2f camera);
    void RenderRect(Graphics& g, SDL_Rect rect, Vector2f position, Vector2f camera);
    Vector2f GetScreenPosition(Vector2f position, int height, Vector2f camera);
};

#endif // PLAY_STATE_H_
