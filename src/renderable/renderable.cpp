#include "../geas_object/geas_object.hpp"

#include "renderable.hpp"

Renderable::Renderable(GeasObject *parent)
    : Transform(parent)
    , has_texture(false)
    , has_colour(false)
    , colour(1.0)
    , size({10.0f, 10.0f})
{

}