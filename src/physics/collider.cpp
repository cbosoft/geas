#include "physics.hpp"
#include "collider.hpp"

CollisionShape::CollisionShape(Physics &owner)
  : owner(owner)
{
  // do nothing
}

Vec2 CollisionShape::get_point_in_world(const Vec2 &point) const
{
  return this->owner.get_position().demote() + point;
}
