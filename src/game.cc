#include "game.h"

#include "SDL2/SDL_image.h"

#include "logging.h"
#include "vector2f.h"
#include "level1.h"

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
    player_velocity_x_(0)
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

  camera_.x = 0;
  camera_.y = 0;

  collisions_ = new Collisions();

  resources_ = new Resources(*renderer_);
  graphics_ = new Graphics(*renderer_);

  player_ = new Player(*resources_, *collisions_);
  world_ = new World(*player_, *collisions_);

  level_ = new Level1(*resources_);
  level_->Initialize(*world_);

  Texture level_texture = level_->GetBackgroundTexture();

  level_background_= new Sprite();
  level_background_->texture = resources_->GetTexture(level_texture);
  level_background_->src_rect.x = 0;
  level_background_->src_rect.y = 0;
  level_background_->src_rect.w = SCREEN_WIDTH;
  level_background_->src_rect.h = SCREEN_HEIGHT;

  if(SDL_QueryTexture(level_background_->texture, NULL, NULL, &level_width_, NULL) < 0) {
    logSDLError("SDL_QueryTexture");
    return false;
  }

  logDebug("Game::Init() successful");

  return true;
}

void Game::Quit() {
  resources_->DestroyTextures();
  delete resources_;
  delete graphics_;
  delete world_;
  delete player_;
  delete level_;
  delete collisions_;

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
  player_->SetVelocityXFactor(player_velocity_x_);
  player_->Update(seconds_elapsed);

  world_->Update(seconds_elapsed);
  level_->Update(seconds_elapsed, *world_);

  Vector2f player_pos = player_->position_;

  // Restrict player to level boundaries
  if(player_pos.x <= 0) {
    player_->position_.x = 0;
  }

  if(player_pos.x >= level_width_ - 36) {
    player_->position_.x = level_width_ - 36;
  }

  // Make the camera follow the player
  if(player_pos.x > ((SCREEN_WIDTH / 2) - 8)) {
    if(player_pos.x < level_width_ - ((SCREEN_WIDTH / 2) + 8)) {
      camera_.x = player_pos.x - (SCREEN_WIDTH / 2) + 8;
    } else {
      camera_.x = level_width_ - SCREEN_WIDTH;
    }
  }
  else {
    camera_.x = 0;
  }

  // Select the right part of the level
  level_background_->src_rect.x = camera_.x;
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
              player_velocity_x_ -= 1;
            }
            break;
          case SDLK_s:
            break;
          case SDLK_d:
            if(!event.key.repeat) {
              player_velocity_x_ += 1;
            }
            break;
          case SDLK_j:
            if(!event.key.repeat) {
              player_->Jump();
            }
            break;
          case SDLK_k:
            if(!event.key.repeat) {
              player_->Shot();
            }
            break;
        }
        break;
      case SDL_KEYUP:
        switch(event.key.keysym.sym) {
          case SDLK_w:
            break;
          case SDLK_a:
            player_velocity_x_ += 1;
            break;
          case SDLK_s:
            break;
          case SDLK_d:
            player_velocity_x_ -= 1;
            break;
        }
        break;
    }
  }
}

void Game::Render(Graphics& graphics) {
  graphics.BeginRender();

  graphics.RenderSprite(level_background_, 0, 0);

  if(player_->health_ >= 1) graphics.RenderTexture(resources_->GetTexture(Texture::HEART), 125, 0);
  if(player_->health_ >= 2) graphics.RenderTexture(resources_->GetTexture(Texture::HEART), 135, 0);
  if(player_->health_ >= 3) graphics.RenderTexture(resources_->GetTexture(Texture::HEART), 145, 0);

  if(player_->reloading_) {
    graphics.RenderSprite(player_->reloading_animation_, 62, 0);
  } else {
    if(player_->shells_ >= 1) graphics.RenderTexture(resources_->GetTexture(Texture::SHELL), 60, -1);
    if(player_->shells_ >= 2) graphics.RenderTexture(resources_->GetTexture(Texture::SHELL), 70, -1);
    if(player_->shells_ >= 3) graphics.RenderTexture(resources_->GetTexture(Texture::SHELL), 80, -1);
  }

  RenderCharacter(graphics, *player_, camera_);
#ifdef DEBUG
  RenderRect(graphics, player_->hitbox_, player_->position_, camera_);
#endif // DEBUG

  std::vector<Character*>* characters = world_->GetCharacters();
  for(std::vector<Character*>::size_type i = 0; i < characters->size(); i++) {
    Character* character = (*characters)[i];
    RenderCharacter(graphics, *character, camera_);

#ifdef DEBUG
    if(collisions_->DoCollide(player_, character)) {
      RenderRect(graphics, character->hitbox_, character->position_, camera_);
    }
#endif // DEBUG
  }

  if(player_->has_text_) {
    graphics.RenderTextCentered(*player_->text_, SCREEN_WIDTH, 20);
  }

  graphics.RenderText(std::to_string(player_->score_), 4, 0);

  graphics.EndRender();
}

/**
 * This method renders a character on the screen.
 *
 * Characters use world coordinates where (0,0) is bottom left of the world.
 * Render methods use screen coordinates where (0,0) is the top left of the screen.
 * The camera uses world coordinates to indicate where we are looking on the world.
 */
void Game::RenderCharacter(Graphics& g, Character& character, Vector2f camera) {
  Sprite* sprite = character.GetSprite();
  Vector2f screen = GetScreenPosition(character.position_, sprite->src_rect.h, camera);
  g.RenderSprite(sprite, screen.x, screen.y);
}

void Game::RenderSprite(Graphics& g, Sprite* sprite, Vector2f position, Vector2f camera) {
  Vector2f screen = GetScreenPosition(position, sprite->src_rect.h, camera);
  g.RenderSprite(sprite, screen.x, screen.y);
}

void Game::RenderRect(Graphics& g, SDL_Rect rect, Vector2f position, Vector2f camera) {
  Vector2f screen = GetScreenPosition(position, rect.h, camera);

  SDL_Rect target;
  target.x = screen.x + rect.x;
  target.y = screen.y + rect.y;
  target.w = rect.w;
  target.h = rect.h;
  g.RenderRect(&target);
}

Vector2f Game::GetScreenPosition(Vector2f position, int height, Vector2f camera) {
  float rel_cam_x = position.x - camera.x;
  float rel_cam_y = position.y - camera.y;

  Vector2f screen;
  screen.x = rel_cam_x;
  screen.y = SCREEN_HEIGHT - rel_cam_y - height;

  return screen;
}
