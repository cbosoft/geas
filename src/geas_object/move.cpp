#include "geas_object.hpp"

void GeasObject::move(int v)
{
    this->physics->driving_direction = v;
}
