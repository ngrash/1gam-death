#ifndef STATE_MANAGER_H_
#define STATE_MANAGER_H_

#include <vector>

#include "SDL2/SDL.h"

#include "state.h"
#include "graphics.h"

class StateManager {
  public:
    StateManager();
    ~StateManager();

    void PushState(State* state);

    void HandleEvent(SDL_Event& event);
    void Update(float seconds_elapsed);
    void Draw(Graphics& graphics);

    void Quit();
    bool IsRunning();
  private:
    bool running_;
    std::vector<State*> states_;
};

#endif // STATE_MANAGER_H_
