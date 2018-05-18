#include "resources.h"

#include <SDL2/SDL_image.h>
#include "logging.h"

Resources::Resources(SDL_Renderer& renderer)
  : textures_((int)Texture::_LAST_ELEMENT_, nullptr),
    renderer_(renderer) {}

SDL_Texture *Resources::LoadTexture(Texture texture) {
  SDL_Texture *tex = nullptr;

  switch(texture) {
    case Texture::PLAYER_IDLE:
      tex = LoadTexture("assets/player_idle.png");
      break;
    case Texture::PLAYER_WALKING:
      tex = LoadTexture("assets/player_walking.png");
      break;
    case Texture::ZOMBIE_IDLE:
      tex = LoadTexture("assets/zombie_idle.png");
      break;
    case Texture::ZOMBIE_WALKING:
      tex = LoadTexture("assets/zombie_walking.png");
      break;
  }

  return tex;
}

void Resources::DestroyTextures() {
  for(int i = 0; i < (int)Texture::_LAST_ELEMENT_; i++) {
    if(textures_[i] != nullptr) {
      SDL_DestroyTexture(textures_[i]);
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
