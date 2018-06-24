#include "level_intro_state.h"

#include "state_manager.h"

LevelIntroState::LevelIntroState(SDL_Texture* texture) :
  texture_(texture),
  intro_duration_(0)
{}

void LevelIntroState::Initialize(StateManager&) {
}

void LevelIntroState::HandleEvent(StateManager&, SDL_Event&) {

}

void LevelIntroState::Update(StateManager& state_manager, float seconds_elapsed) {
  intro_duration_ += seconds_elapsed;
  if(intro_duration_ >= 3) {
    state_manager.PopState();
  }
}

void LevelIntroState::Draw(Graphics& graphics) {
  graphics.RenderTexture(texture_, 0, 0);
}
