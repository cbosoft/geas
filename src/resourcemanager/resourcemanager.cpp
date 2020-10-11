#include <fstream>
#include <sstream>

#include "resourcemanager.hpp"

ResourceManager::ResourceManager()
{

}

std::string read_text_file(std::string filename)
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
