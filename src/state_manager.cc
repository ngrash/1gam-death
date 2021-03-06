#include "state_manager.h"

#include "state.h"

StateManager::StateManager() :
  running_(true)
{}

StateManager::~StateManager() {
  for(std::vector<State*>::size_type i = 0; i < states_.size(); i++) {
    State* state = states_[i];
    delete state;
  }
}

void StateManager::PushState(State* state) {
  states_.push_back(state);
  state->Initialize(*this);
}

void StateManager::PopState() {
  delete states_.back();
  states_.pop_back();
}

void StateManager::HandleEvent(SDL_Event& event) {
  if(event.type == SDL_QUIT
     || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) {
    Quit();
  }
  else {
    states_.back()->HandleEvent(*this, event);
  }
}

void StateManager::Update(float seconds_elapsed) {
  states_.back()->Update(*this, seconds_elapsed);
}

void StateManager::Draw(Graphics& graphics) {
  states_.back()->Draw(graphics);
}

void StateManager::Quit() {
  running_ = false;
}

bool StateManager::IsRunning() {
  return running_;
}
