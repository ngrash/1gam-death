#include "bat_state_asleep.h"

#include "bat.h"

void BatStateAsleep::Initialize(Bat& bat) {
  bat.animation_->Reset();
  bat.animation_->texture = bat.world_.GetResources().GetTexture(Texture::BAT_ASLEEP);
}

void BatStateAsleep::Update(float, Bat&) {
  // A sleeping bat does nothing.
}
