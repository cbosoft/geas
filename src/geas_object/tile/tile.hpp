#pragma once

#include "../geas_object.hpp"

class Tile final : public GeasObject {
public:
    Tile(Transform *parent, float s, const std::string &texture_path, bool fixed, bool collision);
    Tile(Transform *parent, float s, const Vec4 &colour, bool fixed, bool collision);
    ~Tile() override =default;

    void update() override {};

};