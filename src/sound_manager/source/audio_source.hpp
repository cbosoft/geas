#pragma once

#include <AL/al.h>

#include "../../util/audio/audio.hpp"
#include "../../vector/vector.hpp"
#include "../../transform/transform.hpp"

class AudioSource : public Transform {
public:
    ~AudioSource();

    void play() const;
    void pause() const;
    void stop() const;
    void set_pitch(float v) const;
    void set_gain(float v) const;
    void set_position(const Vec3 &position) const;
    void set_velocity(const Vec3 &velocity) const;
    void set_looping() const;
    void set_play_once() const;

    [[nodiscard]] int status() const;

    friend class SoundManager;

private:
    AudioSource(Transform *parent, const AudioSample *sample);

    unsigned int _source;
    unsigned int _buffer;
};