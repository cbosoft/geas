#include <iostream>

#include "player.hpp"

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

    if (this->driving_direction && this->contact_bottom()) {
        this->renderable()->set_anim_loop("run");
    }
    else {
        this->renderable()->set_anim_loop("idle");
    }

    float x = this->driving_accel*static_cast<float>(this->driving_direction);
    this->physics->add_impulse(Vec2({x, y}));

    GeasObject::update();

}
