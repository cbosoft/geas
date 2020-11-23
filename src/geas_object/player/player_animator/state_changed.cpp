#include "player_animator.hpp"
#include "../../../geas_object/geas_object.hpp"


void PlayerAnimator::set_state(int horizontal_speed, bool on_ground)
{
    this->_horizontal_speed = horizontal_speed;
    this->_on_ground = on_ground;

    std::string loop_name = "idle";
    if (this->_on_ground && this->_horizontal_speed) {
        loop_name = "run";
    }

    this->owner.renderable()->set_anim_loop(loop_name);
}