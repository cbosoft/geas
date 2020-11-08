#include <sstream>
#include <fstream>

#include "resourcemanager.hpp"

json ResourceManager::get_json(const std::string &filename) const
{
    std::string abs_filename = this->get_abs_path(filename);
    std::ifstream ifs(abs_filename);

    json rv;
    if (ifs.good()) {
        ifs >> rv;
    }

    return rv;
}
