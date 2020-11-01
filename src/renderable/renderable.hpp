#pragma once

#include <list>

#include "../transform/transform.hpp"

class GeasObject;
class Renderable final : public Transform {
public:
    Renderable(GeasObject *parent);
    ~Renderable() =default;

    std::list<Vec2> points;

    bool has_texture;
    std::string texture_path;

    bool has_colour;
    Vec4 colour;

    Vec2 size;
};