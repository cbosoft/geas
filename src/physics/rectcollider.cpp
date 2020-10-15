#include "collider.hpp"


RectCollider::RectCollider(Physics &owner, Vec2 bl_offset, Vec2 size)
  : CollisionShape(owner)
    , bl_offset(bl_offset)
    , size(size)
{
  // do nothing
}

RectCollider::~RectCollider()
{
  // do nothing
}

Vec2 RectCollider::get_centre() const
{
  Vec2 bl = this->get_point_in_world(this->bl_offset);
  return bl + this->size*0.5;
}

Vec2 RectCollider::get_nearest(const Vec2 &p) const
{
  std::list<Vec2> corners;
  Vec2 bl = this->get_point_in_world(this->bl_offset);
  corners.push_back(bl);
  corners.push_back(bl + Vec2({this->size.x(), 0.0}) );
  corners.push_back(bl + Vec2({0.0, this->size.y()}) );
  corners.push_back(bl + this->size);

  // TODO: get nearest point on the collider to the point p
  (void) p;
  
  return this->get_centre();
}
