#include <sstream>
#include <fstream>
#include "resourcemanager.hpp"


json ResourceManager::get_metadata(const std::string &filename)
{
    auto *de = this->get_entry(filename);
    return de->meta();
}


std::vector<json> ResourceManager::get_matching_metadata(const std::string &pattern)
{
    auto des = this->_db.get_matching(pattern);
    std::vector<json> rv;
    for (const auto &de : des) {
        rv.push_back(de->meta());
    }
    return rv;
}
