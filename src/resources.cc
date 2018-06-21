#include "resources.h"

#include <SDL2/SDL_image.h>
#include "logging.h"

Resources::Resources(SDL_Renderer& renderer) :
  renderer_(renderer),
  textures_((int)Texture::_LAST_ELEMENT_, nullptr)
{}

SDL_Texture *Resources::LoadTexture(Texture texture) {
  SDL_Texture *tex = nullptr;

  switch(texture) {
    case Texture::HEART:
      tex = LoadTexture("assets/heart.png");
      break;
    case Texture::SHELL:
      tex = LoadTexture("assets/shell.png");
      break;
    case Texture::RELOADING:
      tex = LoadTexture("assets/reloading.png");
      break;
    case Texture::PLAYER_IDLE:
      tex = LoadTexture("assets/player_idle.png");
      break;
    case Texture::PLAYER_IDLE_W_SHOTGUN:
      tex = LoadTexture("assets/player_idle_w_shotgun.png");
      break;
    case Texture::PLAYER_WALKING:
      tex = LoadTexture("assets/player_walking.png");
      break;
    case Texture::PLAYER_WALKING_W_SHOTGUN:
      tex = LoadTexture("assets/player_walking_w_shotgun.png");
      break;
    case Texture::ZOMBIE_IDLE:
      tex = LoadTexture("assets/zombie_idle.png");
      break;
    case Texture::ZOMBIE_WALKING:
      tex = LoadTexture("assets/zombie_walking.png");
      break;
    case Texture::ZOMBIE_RISING:
      tex = LoadTexture("assets/zombie_rising.png");
      break;
    case Texture::ZOMBIE_ATTACKING:
      tex = LoadTexture("assets/zombie_attacking.png");
      break;
    case Texture::ZOMBIE_DYING:
      tex = LoadTexture("assets/zombie_dying.png");
      break;
    case Texture::ZOMBIE_DEAD:
      tex = LoadTexture("assets/zombie_dead.png");
      break;
    case Texture::BAT_ASLEEP:
      tex = LoadTexture("assets/bat_asleep.png");
      break;
    case Texture::BAT_FLYING:
      tex = LoadTexture("assets/bat_flying.png");
      break;
    case Texture::BAT_STARTING:
      tex = LoadTexture("assets/bat_starting.png");
      break;
    case Texture::BAT_ATTACKING:
      tex = LoadTexture("assets/bat_attacking.png");
      break;
    case Texture::LEVEL_1:
      tex = LoadTexture("assets/lvl1.png");
      break;
    case Texture::LEVEL_1_INTRO:
      tex = LoadTexture("assets/lvl1_intro.png");
      break;
    case Texture::LEVEL_2:
      tex = LoadTexture("assets/lvl2.png");
      break;
    case Texture::LEVEL_2_INTRO:
      tex = LoadTexture("assets/lvl2_intro.png");
      break;
    case Texture::GAME_OVER:
      tex = LoadTexture("assets/game_over.png");
      break;
    case Texture::CREDITS:
      tex = LoadTexture("assets/credits.png");
      break;
    case Texture::_LAST_ELEMENT_:
      break;
  }

  return tex;
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
