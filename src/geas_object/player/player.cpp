#include "player.hpp"

Player::Player(Transform *parent)
    : GeasObject(parent)
    , jump_force(1.0f)
    , driving_accel(5e-2f)
    , driving_direction(0)
{
  //this->sprite = new Sprite(this, "textures/sprite_sheet.png");
  //this->sprite->request_animation("run");

  auto *r = new Renderable(this);
  r->has_texture = true;
  r->texture_path = "textures/test.png";
  r->size = Vec2({32.0f, 32.0f});
  this->renderable(r);


  this->physics = Physics::create(*this);
  this->physics->set_collider(new RectCollider(this,
        Vec2({0.0, 0.0}),
        r->size)
      );
}
