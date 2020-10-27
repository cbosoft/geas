#include <sstream>
#include <fstream>
#include "resourcemanager.hpp"

std::string ResourceManager::get_metadataname(const std::string &filename) const
{
  std::stringstream ss;
  ss << this->get_abs_path(filename) << ".json";
  return ss.str();
}

json ResourceManager::get_metadata(const std::string &filename) const
{
  std::string metadataname = this->get_metadataname(filename);
  std::ifstream ifs(metadataname);

  json rv;
  if (ifs.good()) {
    ifs >> rv;
  }

  return rv;
}
