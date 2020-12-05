#pragma once

#include <string>
#include <vector>

class AudioSample {
public:
    explicit AudioSample(const std::string &filename);

    [[nodiscard]] const char *data() const;
    [[nodiscard]] unsigned int channels() const;
    [[nodiscard]] unsigned int sample_rate() const;
    [[nodiscard]] unsigned int bits_per_sample() const;
    [[nodiscard]] unsigned int size() const;

private:
    std::vector<char> _data;
    unsigned int _channels;
    int _sample_rate;
    unsigned int _bits_per_sample;
    int _size;

};