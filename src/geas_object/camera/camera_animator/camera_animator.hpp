#pragma once

#include "../../../animator/animator.hpp"

class CameraAnimator : public Animator {
public:
    CameraAnimator(GeasObject &owner);

    void set_state(const std::string &anim);

private:
    void check_state() override;

    bool forwards, paused;
};