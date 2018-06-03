#include "game.h"

#include "SDL2/SDL_image.h"

#include "logging.h"
#include "vector2f.h"
#include "level1.h"
#include "play_state.h"

#define WINDOW_TITLE "DEATH - 65th #1GAM May 2018"
#define WINDOW_X SDL_WINDOWPOS_CENTERED
#define WINDOW_Y SDL_WINDOWPOS_CENTERED
#define SCREEN_WIDTH 160
#define SCREEN_HEIGHT 144
#define WINDOW_WIDTH SCREEN_WIDTH * GAME_SCALE
#define WINDOW_HEIGHT SCREEN_HEIGHT * GAME_SCALE

#define RENDERING_DEVICE_INDEX -1

#define TARGET_FPS 60
#define OPTIMAL_FRAME_TIME 1000.0 / TARGET_FPS

Game::Game()
  : renderer_(nullptr),
    window_(nullptr)
{}

bool Game::Init() {
  if(SDL_Init(SDL_INIT_VIDEO) != 0) {
    logSDLError("SDL_Init");
    return false;
  }

  window_ =
    SDL_CreateWindow(
        WINDOW_TITLE,
        WINDOW_X,
        WINDOW_Y,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN);

  if(window_ == nullptr) {
    logSDLError("SDL_CreateWindow");
    return false;
  }

  renderer_ =
    SDL_CreateRenderer(
        window_,
        RENDERING_DEVICE_INDEX,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  if(SDL_SetRenderDrawBlendMode(renderer_, SDL_BLENDMODE_BLEND) != 0) {
    logSDLError("SDL_SetRenderDrawBlendMode");
    return false;
  }

  if((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
    logSDLError("IMG_Init");
    return false;
  }

  if(TTF_Init() < 0) {
    logSDLError("TTF_Init");
    return false;
  }

  resources_ = new Resources(*renderer_);
  graphics_ = new Graphics(*renderer_);

  state_manager_ = new StateManager();
  state_manager_->PushState(new PlayState(*resources_, SCREEN_WIDTH, SCREEN_HEIGHT));

  logDebug("Game::Init() successful");

  return true;
}

void Game::Quit() {
  resources_->DestroyTextures();
  delete state_manager_;
  delete graphics_;
  delete resources_;

  if(renderer_ != nullptr) {
    SDL_DestroyRenderer(renderer_);
  }

  if(window_ != nullptr) {
    SDL_DestroyWindow(window_);
  }

  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
}

void Game::Run() {
  unsigned int last_time = 0;
  unsigned int current_time;
  float seconds_elapsed;

  while(state_manager_->IsRunning()) {
    current_time = SDL_GetTicks();
    seconds_elapsed = (current_time - last_time) / 1000.0;

    HandleInput();
    Update(seconds_elapsed);
    Render(*graphics_);

    if(SDL_GetTicks() - current_time < OPTIMAL_FRAME_TIME) {
      SDL_Delay(OPTIMAL_FRAME_TIME - (SDL_GetTicks() - current_time));
    }

    last_time = current_time;
  }
}

void Game::Update(float seconds_elapsed) {
  state_manager_->Update(seconds_elapsed);
}

void Game::HandleInput() {
  SDL_Event event;

  while(SDL_PollEvent(&event)) {
    state_manager_->HandleEvent(event);
  }
}

void Game::Render(Graphics& graphics) {
  graphics.BeginRender();

  state_manager_->Draw(graphics);

  graphics.EndRender();
}

