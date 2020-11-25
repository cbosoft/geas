#pragma once

#include "../actor.hpp"
#include "../../../transform/transform.hpp"

class Player final : public Actor {
  public:
    Player(Transform *parent);

    void update() override;

    void move(int dir);
    void jump();
    void hurt(float v) override;
    void crouch(bool v);

private:

    float jump_force;
    float driving_accel;
    int driving_direction;
    bool crouching;
    bool should_jump{false};

};
