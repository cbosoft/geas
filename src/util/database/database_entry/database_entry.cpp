#include <sstream>
#include "database_entry.hpp"

DatabaseEntry::DatabaseEntry(int argc, char **argv, char **colv)
{
    (void) argc; // number of columns
    (void) colv; // column names

    // ID = argv[0];

    _path = argv[1];

    if (argv[2]) {
        char c = argv[2][0];
        int i = 1;
        while (c != 0) {
            this->_data.push_back(c);
            c = argv[2][i];
            i++;
        }
    }

    if (argv[3]) {
        std::stringstream ss;
        ss << argv[3];
        ss >> this->_meta;
    }
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