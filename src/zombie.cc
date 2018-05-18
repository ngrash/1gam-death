#include "zombie.h"

Zombie::Zombie(Resources& resources) {
  sprite_ = new Sprite();
  sprite_->render_flip = SDL_FLIP_NONE;
  sprite_->texture = resources.GetTexture(Texture::ZOMBIE_IDLE);
  sprite_->src_rect.x = 0;
  sprite_->src_rect.y = 0;
  sprite_->src_rect.w = 16;
  sprite_->src_rect.h = 16;

  x_ = 90;
  y_ = 70;
}

Zombie::~Zombie() {
  delete sprite_;
}

Sprite* Zombie::GetSprite() {
  return sprite_;
}

int Zombie::GetX() {
  return x_;
}

int Zombie::GetY() {
  return y_;
}

void Zombie::Update(float seconds_elapsed) {
  // TODO
}
