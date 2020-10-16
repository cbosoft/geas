#include "../physics/collider.hpp"
#include "player.hpp"
Player::Player()
{
  this->sprite = new Sprite("textures/sprite_sheet.png");
  this->sprite->request_animation("run");

  this->transform = new Transform(); // no parent transform: this
  // transform is with respect to the global space. In a real game,
  // this should be the child of the world/level space.

  this->physics = Physics::create(*this);
  this->physics->set_collision(new RectCollider(*this->physics,
        Vec2({0.0, 1.0}),
        Vec2({1.0, 1.0}))
      );
}
