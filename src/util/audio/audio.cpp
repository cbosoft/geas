#include "audio.hpp"
#include "../exception.hpp"

#include <cstring>

#include "../../resourcemanager/resourcemanager.hpp"

// written with help from https://indiegamedev.net/2020/02/15/the-complete-guide-to-openal-with-c-part-1-playing-a-sound/

static int convert_to_int(char *s, int n)
{
    int a = 0;
    // Assuming little endian (x86 is, and ARM is by default, so I think I'm safe enough)
    std::memcpy(&a, s, n);
    return a;
}

AudioSample::AudioSample(const std::string &filename)
{
    auto rm = ResourceManager::singleton();
    auto file_contents = rm.read_binary_file(filename);
    char *data_ptr = file_contents.data();

    if (std::strncmp(data_ptr, "RIFF", 4) != 0) {
        throw AudioFormat("Wave file read error: \"RIFF\" missing");
    }
    data_ptr += 8;

    if (std::strncmp(data_ptr, "WAVE", 4) != 0) {
        throw AudioFormat("Wave file read error: \"WAVE\" missing");
    }
    data_ptr += 14;

    this->_channels = convert_to_int(data_ptr, 2);
    data_ptr += 2;

    this->_sample_rate = convert_to_int(data_ptr, 4);
    data_ptr += 10;

    this->_bits_per_sample = convert_to_int(data_ptr, 2);
    data_ptr += 2;

    if (std::strncmp(data_ptr, "data", 4) != 0) {
        throw AudioFormat("Wave file read error: \"data\" missing");
    }
    data_ptr += 4;

    this->_size = convert_to_int(data_ptr, 4);
    data_ptr += 4;

    for (int i = 0; i < this->_size; i++)
        this->_data.push_back(data_ptr[i]);

}

unsigned int AudioSample::channels() const { return this->_channels; }
const char * AudioSample::data() const {return this->_data.data(); }
unsigned int AudioSample::size() const {return this->_size; }
unsigned int AudioSample::bits_per_sample() const {return this->_bits_per_sample; }
unsigned int AudioSample::sample_rate() const {return this->_sample_rate; }