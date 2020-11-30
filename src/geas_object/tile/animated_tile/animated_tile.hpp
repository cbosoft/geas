#pragma once

#include "../tile.hpp"

class AnimatedTile : public Tile {
public:
    AnimatedTile(Transform *parent, float s, const std::string &texture_path);
    AnimatedTile(Transform *parent, float s, const std::string &texture_path, Vec4 collider);
};