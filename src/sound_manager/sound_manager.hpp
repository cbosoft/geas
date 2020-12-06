#pragma once

#include <string>
#include <map>
#include <list>
#include <mutex>

#include <AL/al.h>
#include <AL/alc.h>

#include "../vector/vector.hpp"
#include "../transform/transform.hpp"
#include "source/audio_source.hpp"

class AudioSample;

class SoundManager {
public:
    static SoundManager *singleton();
    ~SoundManager();

    AudioSource *create_source(const std::string& clipname, Transform *parent);

    void update();

private:

    AudioSource *create_source(AudioSample *audio, Transform *parent);
    void clean_up();
    SoundManager();

    ALCdevice *_dev;
    ALCcontext *_ctx;
    std::mutex _mutex;

    std::map<std::string, AudioSample *> _loaded_samples;
    std::list<AudioSource *> _sources;

};