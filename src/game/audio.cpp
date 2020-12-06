#include "game.hpp"
#include "../sound_manager/sound_manager.hpp"

void Game::audio_thread_worker()
{
    auto *sm = SoundManager::singleton();

    while (this->is_alive()) {
        sm->update();
    }
}