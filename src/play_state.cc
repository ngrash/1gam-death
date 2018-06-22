#include "play_state.h"

#include "level1.h"
#include "level2.h"
#include "level_intro_state.h"
#include "logging.h"
#include "state_manager.h"
#include "game_over_state.h"

PlayState::PlayState(Resources& resources, Sound& sound, int screen_width, int screen_height) :
  resources_(resources),
  sound_(sound),
  screen_width_(screen_width),
  screen_height_(screen_height),
  player_velocity_x_(0),
  level_(nullptr),
  level_background_(nullptr)
{
  camera_.y = 0;
  world_ = new World(resources_);
}

PlayState::~PlayState() {
  delete world_;
  delete level_;
  delete level_background_;
}

void PlayState::LoadNextLevel(StateManager& state_manager) {
  player_velocity_x_ = 0;

  int level_number = 0;
  if(level_ != nullptr) {
    level_number = level_->GetNumber();
  }

  Level* next_level;
  switch(level_number) {
    case 0:
      logDebug("LoadNextLevel: Level1");
      next_level = new Level1(resources_, sound_);
      break;
    case 1:
      logDebug("LoadNextLevel: Level2");
      next_level = new Level2(resources_, sound_);
      break;
  }

  LoadLevel(state_manager, next_level);
}

void PlayState::LoadLevel(StateManager& state_manager, Level* level) {
  world_->Release();

  if(level_ != nullptr) {
    delete level_;
    level_ = nullptr;
  }

  if(level_background_ != nullptr) {
    delete level_background_;
    level_background_ = nullptr;
  }

  level_ = level;
  Texture level_texture = level_->GetBackgroundTexture();

  level_background_= new Sprite();
  level_background_->texture = resources_.GetTexture(level_texture);
  level_background_->src_rect.x = 0;
  level_background_->src_rect.y = 0;
  level_background_->src_rect.w = screen_width_;
  level_background_->src_rect.h = screen_height_;

  if(SDL_QueryTexture(level_background_->texture, NULL, NULL, &(world_->level_width_), NULL) < 0) {
    logSDLError("SDL_QueryTexture");
  }

  level_->Initialize(*world_);

  Texture level_intro = level_->GetIntroTexture();
  SDL_Texture* texture = resources_.GetTexture(level_intro);
  state_manager.PushState(new LevelIntroState(texture));
}

void PlayState::Initialize(StateManager& state_manager) {
  logDebug("PlayState::Initialize");
  LoadNextLevel(state_manager);
}

void PlayState::Update(StateManager& state_manager, float seconds_elapsed) {
  Player& player = world_->GetPlayer();

  int player_health = player.health_;

  if(player_health <= 0) {
    state_manager.PushState(new GameOverState(resources_, player.score_));
  }

  player.SetVelocityXFactor(player_velocity_x_);
  player.Update(seconds_elapsed);

  world_->Update(seconds_elapsed);
  level_->Update(seconds_elapsed, *world_, state_manager);
  if(level_->IsLevelOver()) {
    LoadNextLevel(state_manager);
    return;
  }

  // Player took damage
  if(player_health != player.health_) {
    sound_.PlaySample(Sample::DAMAGE);
  }

  Vector2f player_pos = player.position_;

  // Restrict player to level boundaries
  if(player_pos.x <= 0) {
    player.position_.x = 0;
  }

  if(player_pos.x >= world_->level_width_ - 53) {
    player.position_.x = world_->level_width_ - 53;
  }

  // Make the camera follow the player
  if(player_pos.x > ((screen_width_ / 2) - 8)) {
    if(player_pos.x < world_->level_width_ - ((screen_width_ / 2) + 8)) {
      camera_.x = player_pos.x - (screen_width_ / 2) + 8;
    } else {
      camera_.x = world_->level_width_ - screen_width_;
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

  Player& player = world_->GetPlayer();
  Resources& resources = world_->GetResources();

  if(player.health_ >= 1) graphics.RenderTexture(resources.GetTexture(Texture::HEART), 125, 0);
  if(player.health_ >= 2) graphics.RenderTexture(resources.GetTexture(Texture::HEART), 135, 0);
  if(player.health_ >= 3) graphics.RenderTexture(resources.GetTexture(Texture::HEART), 145, 0);

  if(player.reloading_) {
    graphics.RenderSprite(player.reloading_animation_, 62, 0);
  } else {
    if(player.shells_ >= 1) graphics.RenderTexture(resources.GetTexture(Texture::SHELL), 60, -1);
    if(player.shells_ >= 2) graphics.RenderTexture(resources.GetTexture(Texture::SHELL), 70, -1);
    if(player.shells_ >= 3) graphics.RenderTexture(resources.GetTexture(Texture::SHELL), 80, -1);
  }

  RenderCharacter(graphics, player, camera_);
#ifdef DEBUG
  RenderRect(graphics, player.hitbox_, player.position_, camera_);
#endif // DEBUG

  std::vector<Character*>* characters = world_->GetCharacters();
  for(std::vector<Character*>::size_type i = 0; i < characters->size(); i++) {
    Character* character = (*characters)[i];
    RenderCharacter(graphics, *character, camera_);

#ifdef DEBUG
    //if(collisions_->DoCollide(player, character)) {
      RenderRect(graphics, character->hitbox_, character->position_, camera_);
    //}
#endif // DEBUG
  }

  if(player.has_text_) {
    graphics.RenderTextCentered(*player.text_, screen_width_, 20);
  }

  graphics.RenderText(std::to_string(player.score_), 4, 0);
}

void PlayState::HandleEvent(StateManager& state_manager, SDL_Event& event) {
  Player& player = world_->GetPlayer();

  switch(event.type) {
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
            player.Jump();
          }
          break;
        case SDLK_k:
          if(!event.key.repeat) {
            player.Shot();

            if(!player.unarmed_) {
              if(player.reloading_) {
                sound_.PlaySample(Sample::NO_AMMO);
              } else {
                sound_.PlaySample(Sample::SHOT);
              }
            }
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
