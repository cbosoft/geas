#pragma once

#include <vector>

#include "../animation.hpp"
#include "../../geas_object/actor/actor.hpp"

class AttackAnimation : public Animation {
public:
    AttackAnimation(Actor &owner, const Vec2 &start_position, float distance, unsigned int len);

    bool update(unsigned int current_frame, unsigned int &next_frame) override;

private:
    Actor &owner;

    void enable_hitbox() const;
    void disable_hitbox() const;
    void position_hitbox() const;

    unsigned int len,i;
    std::vector<Vec2> positions;
};