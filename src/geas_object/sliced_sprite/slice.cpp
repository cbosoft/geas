#include "slice.hpp"
#include "../../renderable/renderable.hpp"

Slice::Slice(Transform *parent, const std::string &sprite, unsigned int variant, const Vec2 &size)
    : GeasObject(parent)
{
    auto *r = new Renderable(this);
    this->renderable(r);
    r->size(size);
    r->set_texture(sprite);
    r->current_frame(variant);
}