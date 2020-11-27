#pragma once

#include "../geas_object.hpp"

class Slice : public GeasObject {
public:
    Slice(Transform *parent, const std::string &sprite, unsigned int variant, const Vec2 &size);
};