#include <sstream>
#include <fstream>
#include "resourcemanager.hpp"

json ResourceManager::get_metadata(const std::string &filename)
{
    auto *de = this->get_entry(filename);
    return de->meta();
}
