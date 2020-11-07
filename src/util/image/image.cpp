#include "stb_image/stb_image.h"
#include "image.hpp"

ImageData::ImageData(std::string filename)
{
  const char *path_cstr = filename.c_str();
  stbi_set_flip_vertically_on_load(true);
  int w, h, n;
  this->_data = stbi_load(path_cstr, &w, &h, &n, 0);
  this->_width = w;
  this->_height = h;
  this->_number_channels = n;
}

ImageData::~ImageData()
{
  stbi_image_free(this->_data);
}

unsigned char *ImageData::full_image() const
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

std::vector<unsigned char> ImageData::sub_frame(unsigned int x, unsigned int y, unsigned int w, unsigned int h) const
{
    std::vector<unsigned char> res;
    for (int yi = y; yi < y + h; yi++) {
        for (int xi = x; xi < x + w; xi++) {
            unsigned int i = this->_number_channels*(xi + this->_width*yi);
            res.push_back(this->_data[i]);
        }
    }
    return res;
}

std::vector<unsigned char> ImageData::sub_frame(unsigned int frame_index) const
{
    // TODO calc x,y,w,h from frame info
}
