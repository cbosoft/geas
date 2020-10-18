#include "../physics/collider.hpp"
#include "player.hpp"
Player::Player()
{
  this->sprite = new Sprite(this, "textures/sprite_sheet.png");
  this->sprite->request_animation("run");


  this->physics = Physics::create(*this);
  this->physics->set_collider(new RectCollider(*this->physics,
        Vec2({0.0, 1.0}),
        Vec2({1.0, 1.0}))
      );
}
