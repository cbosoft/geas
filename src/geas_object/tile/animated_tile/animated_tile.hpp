#pragma once

#include "../tile.hpp"

class AnimatedTile : public Tile {
public:
    AnimatedTile(Transform *parent, const Vec2 &size, const std::string &texture_path);
    AnimatedTile(Transform *parent, const Vec2 &size, const std::string &texture_path, Vec4 collider);
};