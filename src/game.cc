#include "game.h"

#include "SDL2/SDL_image.h"
#include "logging.h"
#include "vector2f.h"

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
    window_(nullptr),
    loop_(true),
    playerVelocityX_(0)
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

  player_ = new Player(*resources_);
  zombie_ = new Zombie(*player_, *resources_);

  logDebug("Game::Init() successful");

  return true;
}

void Game::Quit() {
  resources_->DestroyTextures();
  delete resources_;
  delete graphics_;
  delete player_;
  delete zombie_;

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

  while(loop_) {
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
  player_->SetVelocityXFactor(playerVelocityX_);

  player_->Update(seconds_elapsed);
  zombie_->Update(seconds_elapsed);
}

void Game::HandleInput() {
  SDL_Event event;

  while(SDL_PollEvent(&event)) {
    switch(event.type) {
      case SDL_QUIT:
        loop_ = false;
        break;
      case SDL_KEYDOWN:
        switch(event.key.keysym.sym) {
          case SDLK_ESCAPE:
            loop_ = false;
            break;
          case SDLK_w:
            break;
          case SDLK_a:
            if(!event.key.repeat) {
              playerVelocityX_ -= 1;
            }
            break;
          case SDLK_s:
            break;
          case SDLK_d:
            if(!event.key.repeat) {
              playerVelocityX_ += 1;
            }
            break;
          case SDLK_j:
            if(!event.key.repeat) {
              player_->Jump();
            }
            break;
        }
        break;
      case SDL_KEYUP:
        switch(event.key.keysym.sym) {
          case SDLK_w:
            break;
          case SDLK_a:
            playerVelocityX_ += 1;
            break;
          case SDLK_s:
            break;
          case SDLK_d:
            playerVelocityX_ -= 1;
            break;
        }
        break;
    }
  }
}

void Game::Render(Graphics& graphics) {
  graphics.BeginRender();

  RenderCharacter(graphics, *player_, 0, 0);
  RenderCharacter(graphics, *zombie_, 0, 0);

  graphics.RenderText("DEATH", 65, 30);

  graphics.EndRender();
}

/**
 * This method renders a character on the screen.
 *
 * Characters use world coordinates where (0,0) is bottom left of the world.
 * Render methods use screen coordinates where (0,0) is the top left of the screen.
 * The camera uses world coordinates to indicate where we are looking on the world.
 */
void Game::RenderCharacter(Graphics& g, Character& character, float camX, float camY) {
  Sprite* sprite = character.GetSprite();
  Vector2f position = character.GetPosition();
  float relCamX = position.x - camX;
  float relCamY = position.y - camY;

  float screenX = relCamX;
  float screenY = SCREEN_HEIGHT - relCamY - sprite->src_rect.h;

  g.RenderSprite(sprite, screenX, screenY);
}
