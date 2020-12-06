#include "audio_source.hpp"
#include "../../game/game.hpp"
#include "../../util/exception.hpp"

AudioSource::AudioSource(Transform *parent, const AudioSample *sample)
    :   Transform(parent)
{
    alGenBuffers(1, &this->_buffer);
    ALenum format = 0;
    unsigned int n_channels = sample->channels(), bits_per_sample = sample->bits_per_sample();
    if (n_channels == 1) {
        if (bits_per_sample == 8) {
            format = AL_FORMAT_MONO8;
        }
        else if (bits_per_sample == 16) {
            format = AL_FORMAT_MONO16;
        }
        else {
            // error: unknown format
            throw AudioFormat(Formatter() << "unrecognised format: channels=" << n_channels << ", samplerate=" << bits_per_sample << ".");
        }
    }
    else if (n_channels == 2) {
        if (bits_per_sample == 8) {
            format = AL_FORMAT_STEREO8;
        }
        else if (bits_per_sample == 16) {
            format = AL_FORMAT_STEREO16;
        }
        else {
            // error: unknown format
            throw AudioFormat(Formatter() << "unrecognised format: channels=" << n_channels << ", samplerate=" << bits_per_sample << ".");
        }
    }
    else {
        // error: unknown format
        throw AudioFormat(Formatter() << "unrecognised format: channels=" << n_channels << ", samplerate=" << bits_per_sample << ".");
    }

    alBufferData(this->_buffer, format, sample->data(), sample->size(), sample->sample_rate());

    alGenSources(1, &this->_source);

    // default settings for this source
    alSourcef(this->_source, AL_PITCH, 1);
    alSourcef(this->_source, AL_GAIN, 1.0f);
    alSource3f(this->_source, AL_POSITION, 0, 0, 0);
    alSource3f(this->_source, AL_VELOCITY, 0, 0, 0);
    alSourcei(this->_source, AL_LOOPING, AL_FALSE);
    alSourcei(this->_source, AL_BUFFER, this->_buffer);

    Vec3 pos = this->absolute_position();
    auto *game = Game::singleton();
    auto *scene = game->active_scene();
    if (scene) {
        auto *cam = scene->camera();
        if (cam) {
            pos = pos - cam->absolute_position();
        }
    }
    this->set_position(pos);

}

AudioSource::~AudioSource()
{
    alDeleteSources(1, &this->_source);
    alDeleteBuffers(1, &this->_buffer);
}

int AudioSource::status() const
{
    int state = -1;
    alGetSourcei(this->_source, AL_SOURCE_STATE, &state);
    return state;
}

void AudioSource::play() const
{
    alSourcePlay(this->_source);
}

void AudioSource::pause() const
{
    alSourcePause(this->_source);
}

void AudioSource::stop() const
{
    alSourceStop(this->_source);
}

void AudioSource::set_gain(float v) const
{
    alSourcef(this->_source, AL_GAIN, v);
}

void AudioSource::set_looping() const
{
    alSourcei(this->_source, AL_LOOPING, AL_TRUE);
}

void AudioSource::set_play_once() const
{
    alSourcei(this->_source, AL_LOOPING, AL_FALSE);
}

void AudioSource::set_pitch(float v) const
{
    alSourcef(this->_source, AL_PITCH, v);
}

void AudioSource::set_position(const Vec3 &position) const
{
    alSource3f(this->_source, AL_POSITION, position.x(), position.y(), position.z());
}

void AudioSource::set_velocity(const Vec3 &velocity) const
{
    alSource3f(this->_source, AL_POSITION, velocity.x(), velocity.y(), velocity.z());
}
