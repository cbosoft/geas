#pragma once

#include <string>
#include <vector>

#include <sqlite3.h>

#include "../../json.hpp"

class DatabaseEntry {
public:
    explicit DatabaseEntry(sqlite3_stmt *s);

    [[nodiscard]] const std::string &path() const;
    [[nodiscard]] const std::vector<char> &data() const;
    [[nodiscard]] std::string data_as_string() const;
    [[nodiscard]] const json &meta() const;

private:
    std::string _path;
    std::vector<char> _data;
    json _meta;
};