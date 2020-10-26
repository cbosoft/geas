#pragma once

#include "../geas_object/geas_object.hpp"

class Renderable final {
public:
    Renderable(GeasObject &parent);
    ~Renderable() =default;

private:
    GeasObject &parent;
    // location?
    // points?
    // texture?
};