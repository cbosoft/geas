#include "game.hpp"
#include "../animator/animator.hpp"

void Game::animator_thread_worker()
{
    const std::size_t period = 20; // 50hz -> period of 20 ms
    unsigned int frame_number = 0;
    auto t0 = std::chrono::high_resolution_clock::now();
    while (this->is_alive()) {

        const std::list<Animator *> animators = Animator::animators();
        for (Animator *animator : animators) {
            animator->update(frame_number);
        }

        auto t1 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> fs = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0);
        t0 = t1;
        std::size_t dt = fs.count();
        std::size_t wait_time = period - dt;
        std::this_thread::sleep_for(std::chrono::milliseconds(wait_time));
        frame_number++;
        if (frame_number > 1000)
            frame_number = 0;
    }
}