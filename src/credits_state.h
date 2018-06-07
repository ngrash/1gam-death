#ifndef CREDITS_STATE_H_
#define CREDITS_STATE_H_

#include <SDL2/SDL.h>

#include "state.h"
#include "resources.h"

class CreditsState : public State {
  public:
    CreditsState(Resources& resources);
    void Initialize(StateManager& state_manager);
    void HandleEvent(StateManager& state_manager, SDL_Event& event);
    void Update(StateManager& state_manager, float seconds_elapsed);
    void Draw(Graphics& graphics);
  private:
    SDL_Texture* texture_;
};

#endif // CREDITS_STATE_H_
