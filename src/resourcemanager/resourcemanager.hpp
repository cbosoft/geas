#pragma once

#include <string>
#include <map>
#include <vector>

#include "../util/json.hpp"
#include "../util/database/database.hpp"

class ResourceManager {

  public:
    static ResourceManager& singleton()
    {
      static ResourceManager rv;
      return rv;
    }
    ~ResourceManager();

    [[nodiscard]] std::string read_text_file(const std::string &file_name);
    [[nodiscard]] const std::vector<char> &read_binary_file(const std::string &file_name);
    [[nodiscard]] json get_metadata(const std::string &filename);
    [[nodiscard]] std::vector<json> get_matching_metadata(const std::string &pattern);

  private:
    ResourceManager();

    DatabaseEntry *get_entry(const std::string &path);

    Database _db;
    std::map<std::string, DatabaseEntry *> _entries_cache;
};
