#include "player.hpp"

void Player::update()
{
  // apply position to texture
  Vec3 window_position = this->position->in_window_coords();
  this->quad->update_position(window_position);

  // change position a little
  (*this->position) += Vec2({1.0, 0.0});

}
