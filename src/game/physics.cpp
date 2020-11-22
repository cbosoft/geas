#include "game.hpp"


void Game::physics_thread_worker()
{
    auto t0 = std::chrono::high_resolution_clock::now();
    while (this->is_alive()) {
        auto t1 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> fs = std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0);
        t0 = t1;
        this->time_delta_irl = fs.count(); // us
        this->time_irl += this->time_delta_irl;

        this->time_delta = this->time_delta_irl * this->time_scale;
        this->time += this->time_delta;
        Physics::update();
    }
}

