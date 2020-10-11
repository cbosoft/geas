#pragma once
#include <string>
#include <map>

#include "../shader/shader.hpp"

class ResourceManager {

  public:
    static ResourceManager& singleton()
    {
      static ResourceManager rv;
      return rv;
    }
    ~ResourceManager();

    std::string read_text_file(std::string file_name);
    Shader &get_shader(std::string filename);

  private:
    ResourceManager();

    std::map<std::string, Shader> shader_cache;
};
