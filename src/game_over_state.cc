#include "game_over_state.h"

GameOverState::GameOverState(Resources& resources, int score) {
  texture_ = resources.GetTexture(Texture::GAME_OVER);
}

void GameOverState::Initialize(StateManager& state_manager) {

}

void GameOverState::HandleEvent(StateManager& state_manager, SDL_Event& event) {

}

void GameOverState::Update(StateManager& state_manager, float seconds_elapsed) {

}

void GameOverState::Draw(Graphics& graphics) {
  graphics.RenderTexture(texture_, 0, 0);
}

