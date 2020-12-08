#include "game.hpp"


void Game::push_event(Event *event)
{
    std::scoped_lock<std::mutex> _sl(this->mutex);
    this->events_queue.push_back(event);
}


void Game::events_thread_worker()
{
    while (this->is_alive()) {
        {
            std::scoped_lock<std::mutex> _sl(this->mutex);
            std::list<Event *> surviving;
            for (const auto &event : this->events_queue) {
                if (event->should_run(this->get_time())) {
                    event->run();
                }

                if (event->should_delete()) {
                    delete event;
                }
                else {
                    surviving.push_back(event);
                }

            }
            this->events_queue = surviving;

        }

        // time delay without lock on to stop this thread from lockingup the game object
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}