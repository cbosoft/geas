#pragma once

#include "../../../../animator/animator.hpp"

class TileAnimator : public Animator {
public:
    explicit TileAnimator(GeasObject &owner);

    void load_animations(const std::string &texture) override;

private:
    void check_state() override {}
};