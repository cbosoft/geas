#pragma once

#include <string>
#include <vector>
#include "../../json.hpp"

class DatabaseEntry {
public:
    DatabaseEntry(int argc, char **argv, char **colv);

    [[nodiscard]] const std::string &path() const;
    [[nodiscard]] const std::vector<char> &data() const;
    [[nodiscard]] std::string data_as_string() const;
    [[nodiscard]] const json &meta() const;

private:
    std::vector<char> _data;
    json _meta;
    std::string _path;
};