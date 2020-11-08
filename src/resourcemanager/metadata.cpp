#include <sstream>
#include <fstream>
#include "resourcemanager.hpp"

std::string ResourceManager::get_metadataname(const std::string &filename) const
{
  std::stringstream ss;
  ss << filename << ".json";
  return ss.str();
}

json ResourceManager::get_metadata(const std::string &filename) const
{
  std::string metadataname = this->get_metadataname(filename);
  return this->get_json(metadataname);
}
