#pragma once

#include "../actor.hpp"

class Enemy : public Actor {
public:
    Enemy(Transform *parent, float max_HP);

    void move(int dir) override;
    void jump() override;
    void crouch(bool v) override;

    void update() override;

private:
    float jump_force;
    float driving_accel;
    int driving_direction;
    bool crouching;
    bool should_jump{false};

};