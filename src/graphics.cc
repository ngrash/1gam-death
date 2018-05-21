#include "graphics.h"

#include "logging.h"

Graphics::Graphics(SDL_Renderer& renderer)
  : renderer_(renderer)
{
  font_ = TTF_OpenFont("assets/fonts/alterebro-pixel-font.ttf", 16 * GAME_SCALE);
  if(font_ == NULL) {
    logSDLError("TTF_OpenFont");
  }
}

Graphics::~Graphics() {
  TTF_CloseFont(font_);
}

void Graphics::BeginRender() {
  //SDL_SetRenderDrawColor(&renderer_, 128, 128, 128, 255);
  SDL_SetRenderDrawColor(&renderer_, 128, 128, 128, 255);
  SDL_RenderClear(&renderer_);
}

void Graphics::EndRender() {
  SDL_RenderPresent(&renderer_);
}

void Graphics::RenderText(const std::string& text, const int x, const int y) {
  SDL_Color color = {50, 50, 50};
  SDL_Surface* surface = TTF_RenderText_Solid(font_, text.c_str(), color);
  SDL_Texture* texture = SDL_CreateTextureFromSurface(&renderer_, surface);
  SDL_FreeSurface(surface);

  SDL_Rect dst;
  dst.x = x * GAME_SCALE;
  dst.y = y * GAME_SCALE;

  SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
  SDL_RenderCopy(&renderer_, texture, NULL, &dst);

  SDL_DestroyTexture(texture);
}

void Graphics::RenderTexture(SDL_Texture* texture, const int x, const int y) {
  SDL_Rect dst;
  dst.x = x * GAME_SCALE;
  dst.y = y * GAME_SCALE;

  SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);

  dst.w *= GAME_SCALE;
  dst.h *= GAME_SCALE;

  SDL_RenderCopy(&renderer_, texture, NULL, &dst);
}

void Graphics::RenderSprite(Sprite* sprite, const int x, const int y) {
  SDL_Rect dst;
  dst.x = x * GAME_SCALE;
  dst.y = y * GAME_SCALE;
  dst.w = sprite->src_rect.w * GAME_SCALE;
  dst.h = sprite->src_rect.h * GAME_SCALE;

  SDL_RenderCopyEx(
      &renderer_,
      sprite->texture,
      &sprite->src_rect,
      &dst,
      0,
      NULL,
      sprite->render_flip);
}
