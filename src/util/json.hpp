#pragma once

#include <nlohmann/json.hpp>
using json = nlohmann::json;

template<typename T=std::string, typename K=std::string>
T json_get_or_default(json j, const K &key, const T &default_value)
{
    auto it = j.find(key);
    if (it != j.end())
        return *it;
    return default_value;
}