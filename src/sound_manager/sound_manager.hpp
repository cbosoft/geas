#pragma once

#include <string>
#include <map>
#include <list>
#include <mutex>

#include <AL/al.h>
#include <AL/alc.h>

#include "../vector/vector.hpp"

class AudioSource;
class AudioSample;

class SoundManager {
public:
    static SoundManager *singleton();
    ~SoundManager();

    void play(const std::string& clipname, const Vec3 &at);

private:

    void play(AudioSample *audio, const Vec3 &at);
    void clean_up();
    SoundManager();

    ALCdevice *_dev;
    ALCcontext *_ctx;
    std::mutex _mutex;

    std::map<std::string, AudioSample *> _loaded_samples;
    std::list<AudioSource *> _sources;

};