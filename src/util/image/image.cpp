#include <iostream>
#include "../../resourcemanager/resourcemanager.hpp"
#include "stb_image/stb_image.h"
#include "image.hpp"

ImageData::ImageData(const std::string &filename)
{
  const char *path_cstr = filename.c_str();
  stbi_set_flip_vertically_on_load(true);
  int w, h, n;
  this->_data = nullptr;
  this->_data = stbi_load(path_cstr, &w, &h, &n, 0);
  this->_width = w;
  this->_height = h;
  this->_number_channels = n;

  json metadata = ResourceManager::singleton().get_metadata(filename);
  // linter (clangd) erroneously gives error on json.items(). Ignore it.
  this->_number_frames = 1;
  for (auto& [key, value] : metadata.items()) {
      std::string s_key = std::string(key);
      if (s_key.compare("number_frames") == 0) {
          this->_number_frames = value;
      }
  }

  std::cerr << this->_number_frames << " frames for " << filename << " " << this->width() << std::endl;
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


unsigned int ImageData::number_frames() const
{
    return this->_number_frames;
}
