#include "player.hpp"

Player::Player(Transform *parent)
    : GeasObject(parent)
    , jump_force(1.0f)
    , driving_accel(5e-2f)
    , driving_direction(0)
{
  //this->sprite = new Sprite(this, "textures/sprite_sheet.png");
  //this->sprite->request_animation("run");

  this->renderable(new Renderable(this));


  this->physics = Physics::create(*this);
  this->physics->set_collider(new RectCollider(this,
        Vec2({0.0, 0.0}),
        Vec2({10, 10}))
      );
}
