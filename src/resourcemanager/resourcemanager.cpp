#include <fstream>
#include <sstream>

#include "../util/exception.hpp"
#include "resourcemanager.hpp"

ResourceManager::ResourceManager()
{
    // initialise: open necessary files
}

ResourceManager::~ResourceManager()
{
    // do nothing?
}

std::string ResourceManager::get_abs_path(const std::string &relative_path) const
{
    // TODO: abstract away filesystem
    return relative_path;
}

std::string ResourceManager::read_text_file(const std::string &filename) const
{
    std::string abs = this->get_abs_path(filename);
    std::ifstream ifs(abs);

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
