#pragma once
#include <string>

class ResourceManager {

  public:
    static ResourceManager& GetSingleton()
    {
      static ResourceManager rv;
      return rv;
    }
    ~ResourceManager();

    std::string read_text_file(std::string file_name);

  private:
    ResourceManager();
};
