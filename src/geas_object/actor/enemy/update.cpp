
#include "enemy.hpp"

// Called by physics before update
void Enemy::update()
{
    float y = 0.0f;
    if (this->should_jump) {
        if (this->contact_bottom()) {
            y = this->jump_force;
        }
        this->should_jump = false;
    }

    if (this->driving_direction) {
        Vec2 ls = this->local_scale();
        ls.x(static_cast<float>(this->driving_direction));
        this->local_scale(ls);
    }

    float x = this->driving_accel*static_cast<float>(this->driving_direction);
    this->physics->add_impulse(Vec2({x, y}));

    GeasObject::update();

}
