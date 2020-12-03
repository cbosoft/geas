#include "game.hpp"

#ifdef DEBUG

void Game::show_colliders(bool v)
{
    this->_show_colliders = v;
}

bool Game::should_show_colliders() const
{
    return this->_show_colliders;
}

#endif