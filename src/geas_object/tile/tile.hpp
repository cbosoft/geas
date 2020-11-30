#pragma once

#include "../geas_object.hpp"

class Tile : public GeasObject {
public:
    // TODO: need to tidy up construction
    // really need 4 ctors?
    Tile(Transform *parent, float s, const std::string &texture_path);
    Tile(Transform *parent, float s, const std::string &texture_path, Vec4 collider);
    Tile(Transform *parent, float s, const std::string &texture_path, bool fixed, bool collision);
    Tile(Transform *parent, float s, const Vec4 &colour, bool fixed, bool collision);
    ~Tile() override =default;

    void update() override {};
    void set_variant(unsigned int layer, unsigned int frame) const;

};