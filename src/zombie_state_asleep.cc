#include "zombie_state_asleep.h"

#include "zombie.h"

void ZombieStateAsleep::Initialize(Zombie& zombie) {
  // A sleeping zombie is invisible
  zombie.animation_->frame_duration = 1;
  zombie.animation_->texture = nullptr;
  zombie.animation_->num_frames = 0;
}

void ZombieStateAsleep::Update(float seconds_elapsed, Zombie& zombie) {
  // A sleeping zombie does nothing.
}
