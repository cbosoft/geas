#pragma once

#include "../actor.hpp"
#include "../../../transform/transform.hpp"

class Player final : public Actor {
  public:
    Player(Transform *parent);

    void update() override;

    void move(int dir) override;
    void jump() override;
    void hurt(float v) override;
    void crouch(bool v) override;

private:

    float jump_force;
    float driving_accel;
    int driving_direction;
    bool crouching;
    bool should_jump{false};

};
