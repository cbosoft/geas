#include <iostream>
#include "../../resourcemanager/resourcemanager.hpp"
#include "stb_image/stb_image.h"
#include "image.hpp"

ImageData::ImageData(const std::string &filename)
    : _number_layers(1)
{
    auto &rm = ResourceManager::singleton();
    std::vector<char> imdata = rm.read_binary_file(filename);
    json metadata = rm.get_metadata(filename);

    stbi_set_flip_vertically_on_load(true);
    int w, h, n;
    this->_data = nullptr;

    auto *data = (unsigned char *)imdata.data();
    this->_data = stbi_load_from_memory(data, imdata.size(), &w, &h, &n, 0);
    this->_width = w;
    this->_height = h;
    this->_number_channels = n;

    // linter (clangd) erroneously gives error on json.items(). Ignore it.
    this->_number_frames_x = 1;
    this->_number_frames_y = 1;
    for (auto& [key, value] : metadata.items()) {
        std::string s_key = std::string(key);
        if (s_key == "number_frames") {
            if (value.is_number()) {
                this->_number_frames_x = value;
            }
            else if (value.is_array()) {
                this->_number_frames_x = value[0];
                this->_number_frames_y = value[1];
            }
            else {
                // TODO exception
            }
        }
        else if (s_key == "number_layers") {
            this->_number_layers = value;
        }
    }

}

ImageData::~ImageData()
{
  stbi_image_free(this->_data);
}

unsigned char *ImageData::data() const
{
    return this->_data;
}

unsigned int ImageData::width() const
{
    return this->_width;
}

unsigned int ImageData::height() const
{
    return this->_height;
}

unsigned int ImageData::number_channels() const
{
    return this->_number_channels;
}


unsigned int ImageData::number_frames_x() const
{
    return this->_number_frames_x;
}


unsigned int ImageData::number_frames_y() const
{
    return this->_number_frames_y;
}

unsigned int ImageData::number_layers() const
{
    return this->_number_layers;
}