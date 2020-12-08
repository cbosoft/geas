#include "game.hpp"


void Game::physics_thread_worker()
{
    auto start_time = std::chrono::high_resolution_clock::now(), previous_time = start_time;
    while (this->is_alive()) {
        auto now = std::chrono::high_resolution_clock::now();
        unsigned int dt_us = std::chrono::duration_cast<std::chrono::microseconds>(now - previous_time).count();
        unsigned int t = std::chrono::duration_cast<std::chrono::milliseconds>(now - start_time).count();
        float dt_s = static_cast<float>(dt_us)*1e-6f;
        this->time_delta_irl = dt_s;

        previous_time = now;
        this->time_irl = static_cast<float>(t);

        this->time_delta = this->time_delta_irl * this->time_scale;
        this->time += this->time_delta;
        Physics::update();
    }
}

