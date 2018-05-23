#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "sprite.h"

#define GAME_SCALE 5

class Graphics {
  public:
    Graphics(SDL_Renderer& renderer);
    void BeginRender();
    void EndRender();
    void RenderText(const std::string& text, const int x, const int y);;
    void RenderTexture(SDL_Texture* texture, const int x, const int y);
    void RenderSprite(Sprite* sprite, const int x, const int y);
    void RenderRect(SDL_Rect* rect);
    ~Graphics();
  private:
    SDL_Renderer& renderer_;
    TTF_Font* font_;
};

#endif // GRAPHICS_H_
