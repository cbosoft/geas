#include "tile.hpp"

Tile::Tile(Transform *parent, bool fixed, bool collision)
    : GeasObject(parent)
{
    this->physics = Physics::create(*this);
    this->physics->set_fixed(fixed);

    if (collision) {
        this->physics->set_collider(new RectCollider(this,
                                                     Vec2(),
                                                     Vec2({16.0f, 16.0f})));
    }

    auto *r = new Renderable(this);
    this->renderable(r);
    r->size = Vec2({16.0f, 16.0f});
    r->colour = Vec4({1.0f, 0.0f, 0.0f, 1.0f});
    r->has_colour = true;
}
