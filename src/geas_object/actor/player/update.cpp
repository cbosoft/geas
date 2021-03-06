#include <iostream>

#include "player.hpp"
#include "player_animator/player_animator.hpp"

// Called by physics before update
void Player::update()
{
    float y = 0.0f;
    if (this->should_jump) {
        if (this->contact_bottom()) {
            y = this->jump_force;
        }
        this->should_jump = false;
    }

    auto *a = (PlayerAnimator *)this->animator();
    float vspeed = this->physics->get_momentum().y();
    a->set_state(this->driving_direction, vspeed>0.1f?1:(vspeed<-0.1f?-1:0), this->contact_bottom(), this->crouching);

    if (this->driving_direction) {
        Vec2 ls = this->local_scale();
        ls.x(static_cast<float>(this->driving_direction));
        this->local_scale(ls);
    }

    float x = this->driving_accel*static_cast<float>(this->driving_direction);
    this->physics->add_impulse(Vec2({x, y}));

    GeasObject::update();

}
