#include "game.hpp"
#include "../behaviour/behaviour.hpp"


void Game::behaviour_thread_worker()
{
    while (this->is_alive()) {
        Behaviour::update_behaviours();
        std::this_thread::sleep_for(std::chrono::microseconds(100));
    }
}

