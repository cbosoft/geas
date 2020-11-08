#pragma once

#include <map>
#include <string>
#include "../json.hpp"

class ImageData {

  public:
    explicit ImageData(const std::string &filename);
    ~ImageData();

    [[nodiscard]] unsigned char *data() const;
    [[nodiscard]] unsigned int width() const;
    [[nodiscard]] unsigned int height() const;
    [[nodiscard]] unsigned int number_channels() const;
    [[nodiscard]] unsigned int number_frames() const;

private:

    unsigned char *_data;
    unsigned int _width, _height, _number_channels, _number_frames;
};
