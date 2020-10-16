#include "player.hpp"

void Player::update()
{
  // apply position to texture
  Vec3 window_position = this->position->in_window_coords();
  this->sprite->update_position(window_position);
}
