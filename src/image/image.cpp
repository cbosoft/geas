#include "../stb_image/stb_image.h"
#include "image.hpp"

ImageData::ImageData(std::string filename)
{
  const char *path_cstr = filename.c_str();
  this->data = stbi_load(path_cstr, &this->width, &this->height, &this->nChannels, 0);
}

ImageData::~ImageData()
{
  stbi_image_free(this->data);
}
