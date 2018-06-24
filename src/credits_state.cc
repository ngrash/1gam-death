#include "credits_state.h"

CreditsState::CreditsState(Resources& resources) {
  texture_ = resources.GetTexture(Texture::CREDITS);
}

void CreditsState::Initialize(StateManager&) {

}

void CreditsState::HandleEvent(StateManager&, SDL_Event&) {

}

void CreditsState::Update(StateManager&, float) {

}

void CreditsState::Draw(Graphics& graphics) {
  graphics.RenderTexture(texture_, 0, 0);
}

