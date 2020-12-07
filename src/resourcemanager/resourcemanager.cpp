#include <fstream>
#include <sstream>

#include "../util/exception.hpp"
#include "resourcemanager.hpp"

ResourceManager::ResourceManager()
    :   _db("geas_files.db")
{
    // initialise: open necessary files
}

ResourceManager::~ResourceManager()
{
    for (const auto &kv : this->_entries_cache) {
        delete kv.second;
    }
}

DatabaseEntry *ResourceManager::get_entry(const std::string &path)
{
    auto it = this->_entries_cache.find(path);
    if (it != this->_entries_cache.end()) {
        return it->second;
    }

    auto *de = this->_db.get(path);
    this->_entries_cache[path] = de;
    return de;
}

std::string ResourceManager::read_text_file(const std::string &path)
{
    auto *de = this->get_entry(path);
    return de->data_as_string();
}

const std::vector<char> &ResourceManager::read_binary_file(const std::string &path)
{
    auto *de = this->get_entry(path);
    return de->data();
}
