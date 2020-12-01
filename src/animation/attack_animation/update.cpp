#include "attack_animation.hpp"

bool AttackAnimation::update(unsigned int current_frame, unsigned int &next_frame)
{
    (void)current_frame;
    (void)next_frame;

    Vec2 relative_position;

    if (this->i == 0) {
        // run as attack animation starts
        this->enable_hitbox();
    }
    else if (this->i >= this->len) {
        // run as attack animation ends
        this->i = 0;
        this->disable_hitbox();
        return false;
    }

    this->i++;
    this->position_hitbox();
    return true;
}