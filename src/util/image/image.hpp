#pragma once

#include <map>
#include <string>
#include "../json.hpp"

class ImageData {

  public:
    explicit ImageData(const std::string &filename);
    ~ImageData();

    unsigned char *data() const;
    unsigned int width() const;
    unsigned int height() const;
    unsigned int number_channels() const;
    unsigned int number_frames() const;

private:

    unsigned char *_data;
    unsigned int _width, _height, _number_channels, _number_frames;
};
