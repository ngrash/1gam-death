#include "play_state.h"

#include "level1.h"
#include "level_intro_state.h"
#include "logging.h"
#include "state_manager.h"

PlayState::PlayState(Resources& resources, int screen_width, int screen_height) :
  resources_(resources),
  screen_width_(screen_width),
  screen_height_(screen_height),
  player_velocity_x_(0)
{
  camera_.x = 0;
  camera_.y = 0;

  collisions_ = new Collisions();

  player_ = new Player(resources_, *collisions_);
  world_ = new World(*player_, *collisions_);

  level_ = new Level1(resources_);
  level_->Initialize(*world_);

  Texture level_texture = level_->GetBackgroundTexture();

  level_background_= new Sprite();
  level_background_->texture = resources_.GetTexture(level_texture);
  level_background_->src_rect.x = 0;
  level_background_->src_rect.y = 0;
  level_background_->src_rect.w = screen_width_;
  level_background_->src_rect.h = screen_height_;

  if(SDL_QueryTexture(level_background_->texture, NULL, NULL, &level_width_, NULL) < 0) {
    logSDLError("SDL_QueryTexture");
  }
}

PlayState::~PlayState() {
  delete world_;
  delete player_;
  delete level_;
  delete level_background_;
  delete collisions_;
}

void PlayState::Initialize(StateManager& state_manager) {
  Texture level_intro = level_->GetIntroTexture();
  SDL_Texture* texture = resources_.GetTexture(level_intro);

  state_manager.PushState(new LevelIntroState(texture));
}

void PlayState::Update(StateManager& state_manager, float seconds_elapsed) {
  player_->SetVelocityXFactor(player_velocity_x_);
  player_->Update(seconds_elapsed);

  world_->Update(seconds_elapsed);
  level_->Update(seconds_elapsed, *world_);

  Vector2f player_pos = player_->position_;

  // Restrict player to level boundaries
  if(player_pos.x <= 0) {
    player_->position_.x = 0;
  }

  if(player_pos.x >= level_width_ - 53) {
    player_->position_.x = level_width_ - 53;
  }

  // Make the camera follow the player
  if(player_pos.x > ((screen_width_ / 2) - 8)) {
    if(player_pos.x < level_width_ - ((screen_width_ / 2) + 8)) {
      camera_.x = player_pos.x - (screen_width_ / 2) + 8;
    } else {
      camera_.x = level_width_ - screen_width_;
    }
  }
  else {
    camera_.x = 0;
  }

  // Select the right part of the level
  level_background_->src_rect.x = camera_.x;
}

void PlayState::Draw(Graphics& graphics) {
  graphics.RenderSprite(level_background_, 0, 0);

  if(player_->health_ >= 1) graphics.RenderTexture(resources_.GetTexture(Texture::HEART), 125, 0);
  if(player_->health_ >= 2) graphics.RenderTexture(resources_.GetTexture(Texture::HEART), 135, 0);
  if(player_->health_ >= 3) graphics.RenderTexture(resources_.GetTexture(Texture::HEART), 145, 0);

  if(player_->reloading_) {
    graphics.RenderSprite(player_->reloading_animation_, 62, 0);
  } else {
    if(player_->shells_ >= 1) graphics.RenderTexture(resources_.GetTexture(Texture::SHELL), 60, -1);
    if(player_->shells_ >= 2) graphics.RenderTexture(resources_.GetTexture(Texture::SHELL), 70, -1);
    if(player_->shells_ >= 3) graphics.RenderTexture(resources_.GetTexture(Texture::SHELL), 80, -1);
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
    graphics.RenderTextCentered(*player_->text_, screen_width_, 20);
  }

  graphics.RenderText(std::to_string(player_->score_), 4, 0);
}

void PlayState::HandleEvent(StateManager& state_manager, SDL_Event& event) {
  switch(event.type) {
    case SDL_QUIT:
      state_manager.Quit();
      break;
    case SDL_KEYDOWN:
      switch(event.key.keysym.sym) {
        case SDLK_ESCAPE:
          state_manager.Quit();
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

/**
 * This method renders a character on the screen.
 *
 * Characters use world coordinates where (0,0) is bottom left of the world.
 * Render methods use screen coordinates where (0,0) is the top left of the screen.
 * The camera uses world coordinates to indicate where we are looking on the world.
 */
void PlayState::RenderCharacter(Graphics& g, Character& character, Vector2f camera) {
  Sprite* sprite = character.GetSprite();
  Vector2f screen = GetScreenPosition(character.position_, sprite->src_rect.h, camera);
  g.RenderSprite(sprite, screen.x, screen.y);
}

void PlayState::RenderSprite(Graphics& g, Sprite* sprite, Vector2f position, Vector2f camera) {
  Vector2f screen = GetScreenPosition(position, sprite->src_rect.h, camera);
  g.RenderSprite(sprite, screen.x, screen.y);
}

void PlayState::RenderRect(Graphics& g, SDL_Rect rect, Vector2f position, Vector2f camera) {
  Vector2f screen = GetScreenPosition(position, rect.h, camera);

  SDL_Rect target;
  target.x = screen.x + rect.x;
  target.y = screen.y + rect.y;
  target.w = rect.w;
  target.h = rect.h;
  g.RenderRect(&target);
}

Vector2f PlayState::GetScreenPosition(Vector2f position, int height, Vector2f camera) {
  float rel_cam_x = position.x - camera.x;
  float rel_cam_y = position.y - camera.y;

  Vector2f screen;
  screen.x = rel_cam_x;
  screen.y = screen_height_ - rel_cam_y - height;

  return screen;
}
