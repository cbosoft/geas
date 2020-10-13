#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "texture.hpp"

Texture::Texture()
  : texture_id(0)
{
}

Texture Texture::from_file(std::string image_path)
{
  ImageData image(image_path);
  return Texture(image);
}

Texture::Texture(const ImageData &image)
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