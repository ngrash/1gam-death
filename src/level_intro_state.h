#ifndef LEVEL_INTRO_STATE_H_
#define LEVEL_INTRO_STATE_H_

#include <SDL2/SDL.h>

#include "state.h"

class LevelIntroState : public State {
  public:
    LevelIntroState(SDL_Texture* texture);
    void Initialize(StateManager& state_manager);
    void HandleEvent(StateManager& state_manager, SDL_Event& event);
    void Update(StateManager& state_manager, float seconds_elapsed);
    void Draw(Graphics& graphics);
  private:
    SDL_Texture* texture_;
    float intro_duration_;
};

#endif // LEVEL_INTRO_STATE_H_
