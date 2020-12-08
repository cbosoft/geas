#pragma once

#include <string>
#include <vector>
#include "../../json.hpp"

class DatabaseEntry {
public:
    DatabaseEntry(const std::string &path, const std::vector<char> &data, const std::string &meta);

    [[nodiscard]] const std::string &path() const;
    [[nodiscard]] const std::vector<char> &data() const;
    [[nodiscard]] std::string data_as_string() const;
    [[nodiscard]] const json &meta() const;

private:
    std::string _path;
    std::vector<char> _data;
    json _meta;
};