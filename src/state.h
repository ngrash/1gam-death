#ifndef STATE_H_
#define STATE_H_

#include "SDL2/SDL.h"

#include "graphics.h"

class StateManager;

class State {
  public:
    virtual ~State() {}
    virtual void Initialize(StateManager& state_manager) = 0;
    virtual void HandleEvent(StateManager& state_manager, SDL_Event& event) = 0;
    virtual void Update(StateManager& state_manager, float seconds_elapsed) = 0;
    virtual void Draw(Graphics& graphics) = 0;
};

#endif // STATE_H_
