#pragma once

#include <list>
#include "../vector/vector.hpp"

class Physics;
class CollisionShape {

  public:
    CollisionShape(Physics &owner);
    virtual ~CollisionShape() =default;
    virtual Vec2 get_centre() const =0;
    virtual Vec2 get_nearest(const Vec2 &p) const =0;

    Vec2 get_point_in_world(const Vec2 &p) const;

  private:
    Physics &owner;

};

class RectCollider final: public CollisionShape {

  public:
    RectCollider(Physics &owner, Vec2 bl_offset, Vec2 size);
    ~RectCollider();

    Vec2 get_centre() const override;
    Vec2 get_nearest(const Vec2 &p) const override;

  private:
    Vec2 bl_offset, size;

};

class CircleCollider final: public CollisionShape {

  public:
    CircleCollider(Physics &owner, Vec2 bl_offset, float radius);
    ~CircleCollider();

    Vec2 get_centre() const override;
    Vec2 get_nearest(const Vec2 &p) const override;

  private:
    Vec2 bl;
    float radius;

};

class PolygonCollider final: public CollisionShape {

  public:
    PolygonCollider(Physics &owner, std::list<Vec2> points);
    ~PolygonCollider();

    Vec2 get_centre() const override;
    Vec2 get_nearest(const Vec2 &p) const override;

  private:
    std::list<Vec2> points;

};
