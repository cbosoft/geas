#include "resourcemanager.hpp"

Shader &ResourceManager::get_shader(std::string filename)
{
  auto it = this->shader_cache.find(filename);
  if (it != this->shader_cache.end()) {
    return it->second;
  }

  this->shader_cache[filename] = Shader::from_file(filename);
  return this->shader_cache[filename];
}

