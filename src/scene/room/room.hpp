#pragma once

#include <string>
#include <map>

#include "../scene.hpp"

class Room : public Scene {
public:
    static Room *from_file(const std::string &path);

    void activate() override;

private:
    explicit Room(const std::string &name);

    std::map<std::string, Vec2> tunnel_positions;
};