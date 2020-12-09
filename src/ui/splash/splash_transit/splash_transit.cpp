#include <iostream>

#include "splash_transit.hpp"
#include "../../../game/game.hpp"

SplashTransit::SplashTransit(const std::string &dest, float delay)
    :   Event()
    ,   _dest(dest)
    ,   _trigger_time(Game::singleton()->get_time() + delay)
{
    // do nothing
}

bool SplashTransit::should_run(float time)
{
    return (time >= this->_trigger_time);
}

void SplashTransit::run()
{
    auto *game = Game::singleton();
    game->transition_to(this->_dest);
    this->should_delete(true);
}

void SplashTransit::end()
{
    this->_trigger_time = -1.0;
}