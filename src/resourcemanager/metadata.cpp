#include <sstream>
#include <fstream>
#include "resourcemanager.hpp"

std::string ResourceManager::get_metadataname(std::string filename)
{
  std::stringstream ss;
  ss << filename << ".json";
  return ss.str();
}

json ResourceManager::get_metadata(std::string filename)
{
  std::string metadataname = this->get_metadataname(filename);
  std::ifstream ifs(metadataname);

  json rv;
  if (ifs.good()) {
    ifs >> rv;
  }

  return rv;
}
