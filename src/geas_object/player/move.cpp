#include "geas_object.hpp"

void GeasObject::move(int v)
{
    this->physics->driving_direction = v;
}

void GeasObject::jump()
{
    this->physics->add_impulse(Vec2({0.0f, 1.0f}));
}