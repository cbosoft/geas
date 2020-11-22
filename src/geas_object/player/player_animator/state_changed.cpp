#include "player_animator.hpp"
#include "../../../geas_object/geas_object.hpp"


void PlayerAnimator::horizontal_speed(int hs)
{
    this->_horizontal_speed = hs;
    this->state_changed();
}


void PlayerAnimator::on_ground(bool v)
{
    this->_on_ground = v;
    this->state_changed();
}


void PlayerAnimator::state_changed()
{
    std::string loop_name = "idle";
    if (this->_on_ground && this->_horizontal_speed) {
        loop_name = "run";
    }

    this->owner.renderable()->set_anim_loop(loop_name);
}