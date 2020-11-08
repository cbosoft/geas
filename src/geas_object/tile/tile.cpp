#include "tile.hpp"

Tile::Tile(Transform *parent, float s, const std::string &texture_path, bool fixed, bool collision)
    : GeasObject(parent)
{
    this->physics = Physics::create(*this);
    this->physics->set_fixed(fixed);

    if (collision) {
        this->physics->set_collider(new RectCollider(this,
                                                     Vec2(),
                                                     Vec2(s)));
    }

    auto *r = new Renderable(this);
    r->set_texture(texture_path);
    this->renderable(r);
    r->size(Vec2(s));
    r->colour(Vec4(1.0f));
}
