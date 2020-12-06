#pragma once

#include <AL/al.h>

#include "../../util/audio/audio.hpp"
#include "../../vector/vector.hpp"
#include "../../transform/transform.hpp"

class AudioSource : public Transform {
public:
    AudioSource(Transform *parent, const AudioSample *sample);
    ~AudioSource();

    void play();
    void set_pitch(float v) const;
    void set_gain(float v) const;
    void set_position(const Vec3 &position) const;
    void set_velocity(const Vec3 &velocity) const;
    void set_looping() const;
    void set_play_once() const;

    [[nodiscard]] int status() const;

private:

    unsigned int _source;
    unsigned int _buffer;
};