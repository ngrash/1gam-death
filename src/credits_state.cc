#include "credits_state.h"

CreditsState::CreditsState(Resources& resources) {
  texture_ = resources.GetTexture(Texture::CREDITS);
}

void CreditsState::Initialize(StateManager& state_manager) {

}

void CreditsState::HandleEvent(StateManager& state_manager, SDL_Event& event) {

}

void CreditsState::Update(StateManager& state_manager, float seconds_elapsed) {

}

void CreditsState::Draw(Graphics& graphics) {
  graphics.RenderTexture(texture_, 0, 0);
}

