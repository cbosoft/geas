#include <list>
#include <iostream>

#include "sliced_sprite.hpp"
#include "slice.hpp"

SlicedSprite::SlicedSprite(Transform *parent, const Vec2 &size, const std::string &sprite_path)
    : GeasObject(parent)
{

    // TODO create slices for left, right, top, bottom, topleft, topright, bottomleft, and bottomright.
    const float o = 32.0f;
    std::list<Vec2> sizes {
        Vec2({o, o}),
        Vec2({size.x(), o}),
        Vec2({o, o}),
        Vec2({o, size.y()}),
        size,
        Vec2({o, size.y()}),
        Vec2({o, o}),
        Vec2({size.x(), o}),
        Vec2({o, o})
    };
    std::list<Vec2> positions {
            Vec2(-o),
            Vec2({0.0f, -o}),
            Vec2({size.x(), -o}),
            Vec2({-o, 0.0f}),
            Vec2(0.0f),
            Vec2({size.x(), 0.0f}),
            Vec2({-o, size.y()}),
            Vec2({0.0f, size.y()}),
            size
    };
    auto sz_it = sizes.begin();
    auto ps_it = positions.begin();
    for (unsigned int variant = 0; variant < positions.size(); variant++,sz_it++, ps_it++) {
        auto pos = *ps_it;
        Vec3 sz = (*sz_it).promote(0.0f);
        auto *slice = new Slice(this, sprite_path, variant, sz);
        pos += sz*0.5f; // positions are centres!
        slice->relative_position(pos.promote(0.0f));
    }

}