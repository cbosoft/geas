#pragma once

#include <string>
#include <map>

#include "../scene.hpp"

class Room : public Scene {
public:
    static Room *from_file(const std::string &path);
    static Room *from_json(const json &room_spec);

    void activate() override;

private:
    explicit Room(const std::string &name);

    std::map<std::string, Vec2> tunnel_positions;
};