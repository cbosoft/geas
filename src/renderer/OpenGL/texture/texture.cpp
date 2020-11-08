#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include "texture.hpp"

// Texture *Texture::from_file(std::string image_path)
// {
//   ImageData image(image_path);
//   Texture *texture = new Texture(image);
//   json meta = ResourceManager::singleton().get_metadata(image_path);
//
//   if (!meta.is_null()) {
//     std::cout << "found metadata for " << image_path << std::endl;
//     for (auto &[key, value] : meta.items()) {
//       if (key.compare("number_frames") == 0) {
//         texture->n_animation_frames = value;
//       }
//       else if (key.compare("named_loops") == 0) {
//         json named_loops = value;
//         for (auto &[name, lbub] : named_loops.items()) {
//           texture->animation_bounds_by_name[name] = std::make_pair(lbub[0], lbub[1]);
//         }
//       }
//       else {
//         // other information in meta file: ignore
//       }
//     }
//   }
//
//   return texture;
// }

Texture::Texture(const ImageData &image)
  : glid(0)
  , _number_frames(image.number_frames())
{
  glGenTextures(1, &this->glid);
  glBindTexture(GL_TEXTURE_2D, this->glid);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  unsigned int imtype = image.number_channels() == 3?GL_RGB:GL_RGBA;
  glTexImage2D(GL_TEXTURE_2D,
      0,
      imtype,
      image.width(),
      image.height(),
      0,
      imtype,
      GL_UNSIGNED_BYTE,
      image.data());

  glGenerateMipmap(GL_TEXTURE_2D);

  this->framewidth = 1.0f/static_cast<float>(this->_number_frames);
}

Vec4 Texture::get_rect(unsigned int i) const
{
    float x = this->framewidth * static_cast<float>(i);
    return Vec4({x, 0.0f, this->framewidth, 1.0f});
}

void Texture::use() const
{
  glBindTexture(GL_TEXTURE_2D, this->glid);
}
