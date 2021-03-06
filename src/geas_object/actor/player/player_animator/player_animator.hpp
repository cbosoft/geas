#pragma once

#include "../../../../animator/animator.hpp"

class PlayerAnimator final : public Animator {
public:
    explicit PlayerAnimator(GeasObject &owner);
    ~PlayerAnimator() override =default;

    void set_state(int horizontal_speed, int vertical_speed, bool on_ground, bool crouched);

private:

    void check_state() override;

    int _horizontal_speed;
    int _vertical_speed;
    bool _on_ground;
    //bool _on_wall;
    //bool _attacking;
    bool _crouched;

};