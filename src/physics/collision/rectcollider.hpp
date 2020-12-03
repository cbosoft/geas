#pragma once

#include <list>

#include "../../transform/transform.hpp"
#include "../../vector/vector.hpp"

class GeasObject;

class RectCollider final : public Transform {

public:
    RectCollider(GeasObject *parent, const Vec4 &rect);
    RectCollider(GeasObject *parent, const Vec2 &bl_offset, const Vec2 &size);
    ~RectCollider();

    [[nodiscard]] Vec2 get_centre() const;
    [[nodiscard]] Vec2 get_nearest(const Vec2 &p) const;
    [[nodiscard]] std::pair<Vec2, Vec2> get_nearest(const RectCollider *other) const;
    [[nodiscard]] Vec2 get_surface_normal(const Vec2 &at) const;
    [[nodiscard]] bool intersects(const Vec2 &newbase, const RectCollider *other) const;
    [[nodiscard]] bool contains_point(const Vec2 &pt) const;

    Renderable *renderable() const override;

private:

    std::list<Vec2> get_corners() const;

    Vec2 size;
    Transform tr, br, bl, tl;
    Renderable *_renderable;

};
