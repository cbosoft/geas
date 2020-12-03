#include "player.hpp"
#include "player_animator/player_animator.hpp"

Player::Player(Transform *parent)
    : Actor(parent, 3.0f)
    , jump_force(1.5f)
    , driving_accel(7e-2f)
    , driving_direction(0)
    , crouching(false)
{

  auto *r = new Renderable(this);
  r->set_texture("assets/textures/boy.png");
  r->size(Vec2({32.0f, 32.0f}));
  this->renderable(r);

  this->physics = new Physics(*this);
  this->physics->set_collider(new RectCollider(this,
        Vec4({8.0, 0.0, 16.0, 32.0}))
    );

  auto *p = new PlayerAnimator(*this);
  p->load_animations("assets/textures/boy.png");
  p->speed(0.25);
  this->animator(p);
}
