#ifndef RESOURCES_H_
#define RESOURCES_H_

#include <vector>
#include <string>

#include <SDL2/SDL.h>

enum class Texture {
  HEART,
  SHELL,
  PLAYER_IDLE,
  PLAYER_IDLE_W_SHOTGUN,
  PLAYER_WALKING,
  PLAYER_WALKING_W_SHOTGUN,
  ZOMBIE_IDLE,
  ZOMBIE_WALKING,
  ZOMBIE_RISING,
  LEVEL_1,
  _LAST_ELEMENT_
};

class Resources {
  public:
    Resources(SDL_Renderer& renderer);
    SDL_Texture* GetTexture(Texture texture);
    void DestroyTextures();

  private:
    SDL_Renderer& renderer_;
    std::vector<SDL_Texture*> textures_;

    SDL_Texture* LoadTexture(Texture texture);
    SDL_Texture* LoadTexture(const std::string& file);
};

#endif // RESOURCES_H_
