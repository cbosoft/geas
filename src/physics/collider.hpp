#pragma once

#include <list>
#include <map>
#include "../vector/vector.hpp"
#include "../transform/transform.hpp"

class Physics;
class Collider : public Transform {

  public:
    Collider(Physics &owner);
    virtual ~Collider() =default;
    virtual Vec2 get_centre() const =0;
    virtual Vec2 get_nearest(const Vec2 &p) const =0;
    virtual std::pair<Vec2, Vec2> get_nearest(const Collider *other) const =0;
    Vec2 get_separation_between(const Collider *other) const;

  private:
    Physics &owner;

};

class RectCollider final: public Collider {

  public:
    RectCollider(Physics &owner, Vec2 bl_offset, Vec2 size);
    ~RectCollider();

    Vec2 get_centre() const override;
    Vec2 get_nearest(const Vec2 &p) const override;
    std::pair<Vec2, Vec2> get_nearest(const Collider *other) const override;

  private:
    Vec2 bl_offset, size;

};

class CircleCollider final: public Collider {

  public:
    CircleCollider(Physics &owner, Vec2 bl_offset, float radius);
    ~CircleCollider();

    Vec2 get_centre() const override;
    Vec2 get_nearest(const Vec2 &p) const override;
    std::pair<Vec2, Vec2> get_nearest(const Collider *other) const override;

  private:
    Vec2 bl;
    float radius;

};

class PolygonCollider final: public Collider {

  public:
    PolygonCollider(Physics &owner, std::list<Vec2> points);
    ~PolygonCollider();

    Vec2 get_centre() const override;
    Vec2 get_nearest(const Vec2 &p) const override;
    std::pair<Vec2, Vec2> get_nearest(const Collider *other) const override;

  private:
    std::list<Vec2> points;

};
