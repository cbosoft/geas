#include <list>

#include "collider.hpp"

class RectCollider final: public Collider {

public:
    RectCollider(GeasObject &parent, Vec2 bl_offset, Vec2 size);
    ~RectCollider() override;

    Vec2 get_centre() const override;
    Vec2 get_nearest(const Vec2 &p) const override;
    std::pair<Vec2, Vec2> get_nearest(const Collider *other) const override;
    Vec2 get_surface_normal(const Vec2 &at) const override;

private:

    std::list<Vec2> get_corners() const;

    Vec2 size;

};
