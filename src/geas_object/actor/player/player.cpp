#include "player.hpp"
#include "player_animator/player_animator.hpp"

Player::Player(Transform *parent)
    : Actor(parent, 3.0f)
    , jump_force(1.5f)
    , driving_accel(5e-2f)
    , driving_direction(0)
{
  //this->sprite = new Sprite(this, "textures/sprite_sheet.png");
  //this->sprite->request_animation("run");

  auto *r = new Renderable(this);
  r->set_texture("textures/sprite_sheet.png");
  r->size(Vec2({16.0f, 16.0f}));
  this->renderable(r);


  this->physics = Physics::create(*this);
  this->physics->set_collider(new RectCollider(this,
        Vec2({4.0, 0.0}),
        Vec2({8.0, 8.0}))
      );

  auto *p = new PlayerAnimator(*this);
  p->load_animations("textures/sprite_sheet.png");
  this->animator(p);
  this->animator()->speed(0.25);
}
