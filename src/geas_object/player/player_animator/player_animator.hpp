#pragma once

#include "../../../animator/animator.hpp"

class PlayerAnimator final : public Animator {
public:
    explicit PlayerAnimator(GeasObject &owner);
    ~PlayerAnimator() override =default;

    void horizontal_speed(int hs);
    void on_ground(bool v);

private:
    void state_changed() override;

    int _horizontal_speed;
    bool _on_ground;
    //bool _on_wall;
    //bool _attacking;

};