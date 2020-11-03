#include "player.hpp"

void Player::move(int v)
{
    this->driving_direction = v;
}

void Player::jump()
{
    this->should_jump = true;
}