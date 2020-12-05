#include "sound_manager.hpp"
#include "source/audio_source.hpp"
#include "../util/audio/audio.hpp"

void SoundManager::play(const std::string &clipname, const Vec3 &at)
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

    this->play(to_play, at);
}

void SoundManager::play(AudioSample *audio, const Vec3 &at)
{
    if (!audio)
        return;

    auto *as = new AudioSource(audio);
    as->play();
    (void) at;

    std::scoped_lock<std::mutex> _sl(this->_mutex);
    this->_sources.push_back(as);
}