#pragma once

#include "../../../../animator/animator.hpp"

class EnemyAnimator final : public Animator {
public:
    explicit EnemyAnimator(GeasObject &owner);
    ~EnemyAnimator() override =default;

    void set_state(int horizontal_speed, int vertical_speed, bool on_ground);

private:

    void check_state() override;

    int _horizontal_speed;
    int _vertical_speed;
    bool _on_ground;

};
