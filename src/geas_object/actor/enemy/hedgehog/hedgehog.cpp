#include "hedgehog.hpp"
#include "../../../../behaviour/patroller/patroller.hpp"
#include "../enemy_animator/enemy_animator.hpp"

Hedgehog::Hedgehog(Transform *parent)
    :   Enemy(parent, 3.0f)
{
    [[maybe_unused]] auto *b = new Patroller(this);

    const std::string texture = "assets/textures/boy.png";

    auto *r = new Renderable(this);
    r->set_texture(texture);
    r->size(Vec2({32.0f, 32.0f}));
    this->renderable(r);

    auto *a = new EnemyAnimator(*this);
    a->load_animations(texture);
    a->speed(0.25);
    this->animator(a);
}

void Hedgehog::update()
{
    auto *animator = dynamic_cast<EnemyAnimator *>(this->animator());
    int dx = this->get_driving_direction();
    int dy = static_cast<int>(this->physics->get_momentum().y());
    animator->set_state(dx, dy, this->contact_bottom());

    Enemy::update();
}