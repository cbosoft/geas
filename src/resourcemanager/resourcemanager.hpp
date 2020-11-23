#pragma once
#include <string>
#include <map>

#include "../util/json.hpp"

class ResourceManager {

  public:
    static ResourceManager& singleton()
    {
      static ResourceManager rv;
      return rv;
    }
    ~ResourceManager();

    [[nodiscard]] std::string read_text_file(const std::string &file_name) const;
    [[nodiscard]] std::string get_abs_path(const std::string &relative_path) const;
    [[nodiscard]] json get_metadata(const std::string &filename) const;
    [[nodiscard]] json get_json(const std::string &filename) const;
    // TODO: animation management and caching here

  private:
    ResourceManager();
    [[nodiscard]] std::string get_metadataname(const std::string &filename) const;
};
