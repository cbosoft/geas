#include "sound_manager.hpp"
#include "../game/game.hpp"

void SoundManager::update()
{
    auto *game = Game::singleton();
    Vec3 offset;
    auto *scene = game->active_scene();

    if (scene) {
        auto *camera = scene->camera();

        if (camera) {
            offset = camera->absolute_position();
        }
    }

    const float audio_scale = 0.5f;

    {
        std::scoped_lock<std::mutex> _sl(this->_mutex);
        // update sound pos and play/paused based on its transform
        for (auto *source : this->_sources) {
            if (source->is_enabled() && (source->status() == AL_PAUSED || source->status() == AL_INITIAL)) {
                source->play();
            }
            else if (!source->is_enabled() && source->status() == AL_PLAYING) {
                source->pause();
            }

            if (source->status() == AL_PLAYING) {
                Vec3 position = source->absolute_position() - offset;
                position = position * audio_scale;
                source->set_position(position);
            }
        }
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}