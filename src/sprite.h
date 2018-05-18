#ifndef SPRITE_H_
#define SPRITE_H_

#include <SDL2/SDL.h>

struct Sprite {
  SDL_Texture* texture;
  SDL_Rect src_rect;
  SDL_RendererFlip render_flip;
};

#endif // SPRITE_H_
