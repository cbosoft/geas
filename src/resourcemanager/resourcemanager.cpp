#include <fstream>
#include <sstream>

#include "resourcemanager.hpp"

ResourceManager::ResourceManager()
{
  // do nothing?
}

ResourceManager::~ResourceManager()
{
  // do nothing?
}

std::string ResourceManager::read_text_file(std::string filename)
{
  // TODO: abstract away filesystem
  std::ifstream ifs(filename);
  std::string s;
  std::stringstream ss;

  while (std::getline(ifs, s)) {
    ss << s << "\n";
  }

  return ss.str();
}
