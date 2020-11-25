#include "player_animator.hpp"
#include "../../../geas_object.hpp"


void PlayerAnimator::set_state(int horizontal_speed, int vertical_speed, bool on_ground, bool crouched)
{
    this->_horizontal_speed = horizontal_speed;
    this->_vertical_speed = vertical_speed;
    this->_on_ground = on_ground;
    this->_crouched = crouched;
    this->check_state();
}

void PlayerAnimator::check_state()
{
    Animation *current = this->current_anim();

    // if current animation is still running and cant be interrupted, then don't bother checking.
    if (current && !current->ended(this->current_frame()) && !current->interruptable())
        return;

    std::string loop_name = "idle";
    if (this->_on_ground) {
        if (this->_horizontal_speed) {
            loop_name = (this->_crouched?"crouch_run":"run");
        }
        else {
            if (this->_crouched) {
                loop_name = "crouch";
            }
        }
    }
    else {
        if (this->_vertical_speed > 0) {
            loop_name = "jump";
        }
        else if (this->_vertical_speed < 0) {
            loop_name = "fall";
        }
    }

    if (current && (current->name() == "hurt") && current->ended(this->current_frame())) {
        // if HP <= 0 then loop_name = "dying";
    }

    this->set_current_anim(loop_name);
}