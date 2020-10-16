#include "../physics/collider.hpp"
#include "player.hpp"
Player::Player()
{
  this->sprite = new Sprite("textures/sprite_sheet.png");
  this->sprite->request_animation("run");

  this->position = new WorldPosition(-640.0, 0.0, 0.0);
  this->physics = Physics::create(*this);
  this->physics->set_collision(new RectCollider(*this->physics,
        /* position: */Vec2({0.0, 1.0}),
        /*     size: */Vec2({1.0, 1.0}))
      );
}
