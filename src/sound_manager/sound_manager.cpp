#include "sound_manager.hpp"

SoundManager::SoundManager()
{
    // init openal
    this->_dev = alcOpenDevice(nullptr);
    if (!this->_dev) {
        // error
    }

    this->_ctx = alcCreateContext(this->_dev, nullptr);
    if (!this->_ctx) {
        // error
    }

    if (!alcMakeContextCurrent(this->_ctx)) {
        // error
    }
}

SoundManager::~SoundManager()
{
    // tear down openal
    this->clean_up();
    alcMakeContextCurrent(this->_ctx);
    alcDestroyContext(this->_ctx);
    alcCloseDevice(this->_dev);
}

SoundManager *SoundManager::singleton()
{
    static SoundManager sm;
    return &sm;
}