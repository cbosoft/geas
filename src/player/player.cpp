#include "player.hpp"
Player::Player()
{
  this->quad = new Quad();
  this->quad->update_texture("textures/sprite_sheet.png");

  this->position = new WorldPosition(-640.0, 0.0, 0.0);
}
