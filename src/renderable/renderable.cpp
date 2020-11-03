#include "../geas_object/geas_object.hpp"
#include "../renderer/renderer.hpp"
#include "renderable.hpp"

Renderable::Renderable(GeasObject *parent)
    : Transform(parent)
    , has_texture(false)
    , has_colour(false)
    , colour(1.0)
    , size({10.0f, 10.0f})
    , renderer_data(nullptr)
{

}

Renderable::~Renderable() noexcept
{
    if (this->renderer_data) {
        Renderer *rend = Renderer::get(nullptr);
        rend->clean(this);
    }
}