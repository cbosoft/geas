#include <sstream>
#include "database_entry.hpp"

DatabaseEntry::DatabaseEntry(const std::string &path, const std::vector<char> &data, const std::string &meta)
    :   _path(path)
    ,   _data(data)
{
    if (!meta.empty())
        this->_meta = json::parse(meta);
}


const std::string &DatabaseEntry::path() const
{
    return this->_path;
}

const std::vector<char> &DatabaseEntry::data() const
{
    return this->_data;
}

const json &DatabaseEntry::meta() const
{
    return this->_meta;
}

std::string DatabaseEntry::data_as_string() const
{
    auto *cstr = (char *)alloca(this->_data.size()+1);
    for (unsigned int i = 0; i < this->_data.size(); i++) {
        cstr[i] = this->_data[i];
    }
    cstr[this->_data.size()] = 0;
    return std::string(cstr);
}