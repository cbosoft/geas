#include "sound_manager.hpp"
#include "source/audio_source.hpp"
#include "../util/audio/audio.hpp"

AudioSource *SoundManager::create_source(const std::string &clipname, Transform *parent)
{
    AudioSample *to_play = nullptr;
    {
        std::scoped_lock<std::mutex> _sl(this->_mutex);
        auto it = this->_loaded_samples.find(clipname);
        if (it != this->_loaded_samples.end()) {
            to_play = it->second;
        }
        else {
            to_play = new AudioSample(clipname);
            this->_loaded_samples[clipname] = to_play;
        }
    }

    return this->create_source(to_play, parent);
}

AudioSource *SoundManager::create_source(AudioSample *audio, Transform *parent)
{
    if (!audio)
        return nullptr;

    auto *as = new AudioSource(parent, audio);

    std::scoped_lock<std::mutex> _sl(this->_mutex);
    this->_sources.push_back(as);
    return as;
}