#include "enemy.hpp"

Enemy::Enemy(Transform *parent, float max_HP)
    :   Actor(parent, max_HP)
    ,   jump_force(1.5f)
    ,   driving_accel(7e-3f)
    ,   driving_direction(0)
    ,   crouching(false)
{
    // do nothing
    this->physics = new Physics(*this);
    this->physics->set_collider(Vec4({0.0f, 0.0f, 32.0f, 32.0f}));
}

void Enemy::move(int v)
{
    this->driving_direction += v;

    if (this->driving_direction < -1)
        this->driving_direction = -1;
    else if (this->driving_direction > 1)
        this->driving_direction = 1;
}

void Enemy::jump()
{
    this->should_jump = true;
}

void Enemy::crouch(bool v)
{
    this->crouching = v;
}
