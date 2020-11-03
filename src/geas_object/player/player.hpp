#pragma once

#include "../geas_object.hpp"

class Player final : public GeasObject {
  public:
    Player(Transform *parent);

    void update() override;

    void move(int dir);
    void jump();

private:

    float jump_force;
    float driving_accel;
    int driving_direction;
    bool should_jump{false};

};
