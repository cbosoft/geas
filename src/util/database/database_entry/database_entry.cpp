#include <sstream>
#include "database_entry.hpp"

DatabaseEntry::DatabaseEntry(sqlite3_stmt *s)
{
    // column 0: id
    //int id = sqlite3_column_int(s, 0);

    // column 1: path
    this->_path = (const char *)sqlite3_column_text(s, 1);

    // column 2: data blob
    if (sqlite3_column_type(s, 2) != SQLITE_NULL) {
        int data_size = sqlite3_column_bytes(s, 2);
        auto *data_raw = (char *) sqlite3_column_blob(s, 2);
        for (int i = 0; i < data_size; i++)
            this->_data.push_back(data_raw[i]);
    }

    // column 3: metadata
    if (sqlite3_column_type(s, 3) != SQLITE_NULL) {
        auto *meta_source = (const char *)sqlite3_column_text(s, 3);
        this->_meta = json::parse(meta_source);
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