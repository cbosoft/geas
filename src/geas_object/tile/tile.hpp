#pragma once

#include "../geas_object.hpp"

class Tile final : public GeasObject {
public:
    Tile(Transform *parent, float s, bool fixed, bool collision);
    ~Tile() override =default;

    void update() override {};

};