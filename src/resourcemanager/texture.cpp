#include "../image/image.hpp"
#include "resourcemanager.hpp"

Texture *ResourceManager::get_texture(std::string filename)
{
  // TODO filesystem abstraction
  ImageData image(filename);
  auto it = this->texture_cache.find(filename);
  if (it != this->texture_cache.end()) {
    return &it->second;
  }

  this->texture_cache[filename] = Texture::from_file(filename);
  return &this->texture_cache[filename];

}
