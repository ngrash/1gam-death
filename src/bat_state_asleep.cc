#include "bat_state_asleep.h"

#include "bat.h"

void BatStateAsleep::Initialize(Bat& bat) {
  bat.animation_->Reset();
  bat.animation_->texture = bat.resources_.GetTexture(Texture::BAT_ASLEEP);
}

void BatStateAsleep::Update(float seconds_elapsed, Bat& bat) {
  // A sleeping bat does nothing.
}
