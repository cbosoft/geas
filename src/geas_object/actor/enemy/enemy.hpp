#pragma once

#include "../actor.hpp"

class Enemy : public Actor {
public:
    static Enemy *from_spec(Transform *parent, const json &spec);
    Enemy(Transform *parent, float max_HP);

    void move(int dir) override;
    void jump() override;
    void crouch(bool v) override;

    void update() override;

    int get_driving_direction() const;


private:
    float jump_force;
    float driving_accel;
    int driving_direction;
    bool crouching;
    bool should_jump{false};

};