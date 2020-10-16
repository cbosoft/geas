#include "player.hpp"
Player::Player()
{
  this->sprite = new Sprite("textures/sprite_sheet.png");
  this->sprite->request_animation("run");

  this->position = new WorldPosition(-640.0, 0.0, 0.0);
  this->physics = Physics::create(*this);
}
