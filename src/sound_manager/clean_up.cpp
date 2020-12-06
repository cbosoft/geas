#include <iostream>

#include <AL/al.h>

#include "sound_manager.hpp"
#include "source/audio_source.hpp"

void SoundManager::clean_up()
{
    std::scoped_lock<std::mutex> _sl(this->_mutex);
    std::list<AudioSource *> surviving_sources;
    for (AudioSource *source : this->_sources) {
        if (source->status() == AL_STOPPED) {
             delete source;
        }
        else {
            surviving_sources.push_back(source);
        }
    }
    this->_sources = surviving_sources;
}