#include <fstream>
#include <sstream>

#include "../util/exception.hpp"
#include "resourcemanager.hpp"

ResourceManager::ResourceManager()
{
  // do nothing?
}

ResourceManager::~ResourceManager()
{
  // clean up textures
  for (auto kv : this->texture_cache) {
    delete kv.second;
  }
}

std::string ResourceManager::read_text_file(std::string filename)
{
  // TODO: abstract away filesystem
  std::ifstream ifs(filename);

  if (!ifs) {
    throw IOError(Formatter() << "Could not read file \"" << filename << "\"");
  }

  std::string s;
  std::stringstream ss;

  while (std::getline(ifs, s)) {
    ss << s << "\n";
  }

  return ss.str();
}
