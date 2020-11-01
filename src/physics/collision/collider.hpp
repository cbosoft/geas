#pragma once

#include <list>
#include <map>

#include "../../vector/vector.hpp"
#include "../../transform/transform.hpp"

class GeasObject;
class Collider : public Transform {

  public:
    explicit Collider(GeasObject &parent);
    ~Collider() override =default;

    virtual Vec2 get_centre() const =0;
    virtual Vec2 get_nearest(const Vec2 &p) const =0;
    virtual std::pair<Vec2, Vec2> get_nearest(const Collider *other) const =0;
    virtual Vec2 get_surface_normal(const Vec2 &at) const =0;
    Vec2 get_separation_between(const Collider *other) const;

};
