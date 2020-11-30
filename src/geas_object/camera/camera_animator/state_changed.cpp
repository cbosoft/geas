#include <iostream>
#include "camera_animator.hpp"

void CameraAnimator::set_state(const std::string &anim)
{
    if (anim == "fade_out")
        forwards = true;
    else if (anim == "fade_in")
        forwards = false;

    paused = false;

    check_state();
}

void CameraAnimator::check_state()
{
    std::string loop_name = "open";

    if (this->paused) {
        loop_name = (this->forwards ? "shuttered" : "open");
    }
    else {

        Animation *current = this->current_anim();

        if (current && current->ended(this->current_frame())) {
            paused = true;
            this->check_state();
            return;
        }

        loop_name = (this->forwards ? "fade_out" : "fade_in");
    }

    this->set_current_anim(loop_name);
}