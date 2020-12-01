#include "tile.hpp"

Tile::Tile(Transform *parent, float s, const std::string &texture_path)
        : GeasObject(parent)
{
    auto *r = new Renderable(this);
    r->set_texture(texture_path);
    this->renderable(r);
    r->size(Vec2(s));
    r->colour(Vec4(1.0f));
}

Tile::Tile(Transform *parent, float s, const std::string &texture_path, Vec4 rect)
        : GeasObject(parent)
{
    this->physics = new Physics(*this);
    this->physics->set_fixed();

    this->physics->set_collider(rect);

    auto *r = new Renderable(this);
    r->set_texture(texture_path);
    this->renderable(r);
    r->size(Vec2(s));
    r->colour(Vec4(1.0f));
}

Tile::Tile(Transform *parent, float s, const std::string &texture_path, bool fixed, bool collision)
    : GeasObject(parent)
{
    if (collision || !fixed) {
        this->physics = new Physics(*this);
        this->physics->set_fixed(fixed);

        if (collision) {
            this->physics->set_collider(new RectCollider(this,
                                                         Vec2(),
                                                         Vec2(s)));
        }
    }

    auto *r = new Renderable(this);
    r->set_texture(texture_path);
    this->renderable(r);
    r->size(Vec2(s));
    r->colour(Vec4(1.0f));
}

Tile::Tile(Transform *parent, float s, const Vec4 &colour, bool fixed, bool collision)
        : GeasObject(parent)
{
    if (collision || !fixed) {
        this->physics = new Physics(*this);
        this->physics->set_fixed(fixed);

        if (collision) {
            this->physics->set_collider(new RectCollider(this,
                                                         Vec2(),
                                                         Vec2(s)));
        }
    }

    auto *r = new Renderable(this);
    this->renderable(r);
    r->size(Vec2(s));
    r->colour(colour);
}

void Tile::set_variant(unsigned int layer, unsigned int frame) const
{
    auto *r = this->renderable();
    r->current_frame(frame);
    r->layer(layer);
}