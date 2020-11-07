#pragma once

#include <vector>
#include <string>

class ImageData {

  public:
    explicit ImageData(std::string filename);
    ~ImageData();

    unsigned char *full_image() const;
    std::vector<unsigned char> sub_frame(unsigned int x, unsigned int y, unsigned int w, unsigned int h) const;
    std::vector<unsigned char> sub_frame(unsigned int frame_index) const;
    unsigned int width() const;
    unsigned int height() const;
    unsigned int number_channels() const;

private:
    unsigned char *_data;
    unsigned int _width, _height, _number_channels, _number_frames;

};
