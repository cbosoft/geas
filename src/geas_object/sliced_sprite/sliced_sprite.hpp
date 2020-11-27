#pragma once

#include "../geas_object.hpp"

class SlicedSprite : public GeasObject {
public:
    SlicedSprite(Transform *parent, const Vec2 &size, const std::string &sprite_path);
};