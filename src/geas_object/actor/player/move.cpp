#include "player.hpp"

void Player::move(int v)
{
    this->driving_direction += v;

    if (this->driving_direction < -1)
        this->driving_direction = -1;
    else if (this->driving_direction > 1)
        this->driving_direction = 1;
}

void Player::jump()
{
    this->should_jump = true;
}

void Player::crouch(bool v)
{
    this->crouching = v;
}