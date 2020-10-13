#pragma once
#include <string>
#include <map>

#include "../shader/shader.hpp"
#include "../texture/texture.hpp"
#include "../util/json.hpp"

class ResourceManager {

  public:
    friend class Window;

    static ResourceManager& singleton()
    {
      static ResourceManager rv;
      return rv;
    }
    ~ResourceManager();

    std::string read_text_file(std::string file_name);
    Shader &get_shader(std::string filename);
    Texture *get_texture(std::string filename);
    json get_metadata(std::string filename);

  private:
    ResourceManager();
    std::string get_metadataname(std::string filename);

    std::map<std::string, Shader> shader_cache;
    std::map<std::string, Texture *> texture_cache;
};
