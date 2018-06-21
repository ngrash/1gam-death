#include "resources.h"

#include <SDL2/SDL_image.h>
#include "logging.h"

Resources::Resources(SDL_Renderer& renderer) :
  renderer_(renderer),
  textures_((int)Texture::_LAST_ELEMENT_, nullptr)
{}

SDL_Texture *Resources::LoadTexture(Texture texture) {
  switch(texture) {
    case Texture::HEART:
      return LoadTexture("assets/heart.png");
    case Texture::SHELL:
      return LoadTexture("assets/shell.png");
    case Texture::RELOADING:
      return LoadTexture("assets/reloading.png");
    case Texture::PLAYER_IDLE:
      return LoadTexture("assets/player_idle.png");
    case Texture::PLAYER_IDLE_W_SHOTGUN:
      return LoadTexture("assets/player_idle_w_shotgun.png");
    case Texture::PLAYER_WALKING:
      return LoadTexture("assets/player_walking.png");
    case Texture::PLAYER_WALKING_W_SHOTGUN:
      return LoadTexture("assets/player_walking_w_shotgun.png");
    case Texture::ZOMBIE_IDLE:
      return LoadTexture("assets/zombie_idle.png");
    case Texture::ZOMBIE_WALKING:
      return LoadTexture("assets/zombie_walking.png");
    case Texture::ZOMBIE_RISING:
      return LoadTexture("assets/zombie_rising.png");
    case Texture::ZOMBIE_ATTACKING:
      return LoadTexture("assets/zombie_attacking.png");
    case Texture::ZOMBIE_DYING:
      return LoadTexture("assets/zombie_dying.png");
    case Texture::ZOMBIE_DEAD:
      return LoadTexture("assets/zombie_dead.png");
    case Texture::BAT_ASLEEP:
      return LoadTexture("assets/bat_asleep.png");
    case Texture::BAT_FLYING:
      return LoadTexture("assets/bat_flying.png");
    case Texture::BAT_STARTING:
      return LoadTexture("assets/bat_starting.png");
    case Texture::BAT_ATTACKING:
      return LoadTexture("assets/bat_attacking.png");
    case Texture::LEVEL_1:
      return LoadTexture("assets/lvl1.png");
    case Texture::LEVEL_1_INTRO:
      return LoadTexture("assets/lvl1_intro.png");
    case Texture::LEVEL_2:
      return LoadTexture("assets/lvl2.png");
    case Texture::LEVEL_2_INTRO:
      return LoadTexture("assets/lvl2_intro.png");
    case Texture::GAME_OVER:
      return LoadTexture("assets/game_over.png");
    case Texture::CREDITS:
      return LoadTexture("assets/credits.png");
    case Texture::_LAST_ELEMENT_:
      return nullptr;
  }

  return nullptr;
}

void Resources::DestroyTextures() {
  for(int i = 0; i < (int)Texture::_LAST_ELEMENT_; i++) {
    if(textures_[i] != nullptr) {
      SDL_DestroyTexture(textures_[i]);
      textures_[i] = nullptr;
    }
  }
}

SDL_Texture* Resources::GetTexture(Texture texture) {
  if(textures_[int(texture)] == nullptr) {
    textures_[int(texture)] = LoadTexture(texture);
  }
  return textures_[int(texture)];
}

SDL_Texture* Resources::LoadTexture(const std::string& file) {
  SDL_Texture* texture = nullptr;
  SDL_Surface* image = IMG_Load(file.c_str());

  if(image != nullptr) {
    texture = SDL_CreateTextureFromSurface(&renderer_, image);
    SDL_FreeSurface(image);
    if(texture == nullptr) {
      logSDLError("SDL_CreateTextureFromSurface");
    }
  }
  else {
    logSDLError("IMG_Load");
  }

  return texture;
}
