#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../resourcemanager/resourcemanager.hpp"

#include "texture.hpp"

Texture::Texture()
  : texture_id(0)
    , n_animation_frames(1)
{
}

Texture *Texture::from_file(std::string image_path)
{
  ImageData image(image_path);
  Texture *texture = new Texture(image);
  json meta = ResourceManager::singleton().get_metadata(image_path);

  if (!meta.is_null()) {
    std::cout << "found metadata for " << image_path << std::endl;
    for (auto &[key, value] : meta.items()) {
      if (key.compare("number_frames") == 0) {
        texture->n_animation_frames = value;
      }
      else if (key.compare("named_loops") == 0) {
        json named_loops = value;
        for (auto &[name, lbub] : named_loops.items()) {
          texture->animation_bounds_by_name[name] = std::make_pair(lbub[0], lbub[1]);
        }
      }
      else {
        // other information in meta file: ignore
      }
    }
  }

  return texture;
}

Texture::Texture(const ImageData &image)
  : Texture()
{
  glGenTextures(1, &this->texture_id);
  glBindTexture(GL_TEXTURE_2D, this->texture_id);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  unsigned int imtype = image.nChannels == 3?GL_RGB:GL_RGBA;
  glTexImage2D(GL_TEXTURE_2D,
      0,
      imtype,
      image.width,
      image.height,
      0,
      imtype,
      GL_UNSIGNED_BYTE,
      image.data);

  glGenerateMipmap(GL_TEXTURE_2D);
}

void Texture::use()
{
  glBindTexture(GL_TEXTURE_2D, this->texture_id);
}

void Texture::request_animation_bounds(std::string name, unsigned int &lb, unsigned int &ub)
{
  auto it = this->animation_bounds_by_name.find(name);
  if (it != this->animation_bounds_by_name.end()) {
    auto lbub = it->second;
    lb = lbub.first;
    ub = lbub.second;
  }
  else {
    std::cerr << "Warning: failed to set loop with name " << name << std::endl;
  }
}

float Texture::get_inv_n_frames()
{
  static float inv_n = 1.0;
  static unsigned int prev_n = -1;

  if (this->n_animation_frames != prev_n) {
    inv_n = 1.0/float(this->n_animation_frames);
    prev_n = this->n_animation_frames;
  }
  return inv_n;
}

unsigned int Texture::get_id() const
{
  return this->texture_id;
}
