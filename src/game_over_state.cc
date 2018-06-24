#include "game_over_state.h"

GameOverState::GameOverState(Resources& resources) {
  texture_ = resources.GetTexture(Texture::GAME_OVER);
}

void GameOverState::Initialize(StateManager&) {

}

void GameOverState::HandleEvent(StateManager&, SDL_Event&) {

}

void GameOverState::Update(StateManager&, float) {

}

void GameOverState::Draw(Graphics& graphics) {
  graphics.RenderTexture(texture_, 0, 0);
}

