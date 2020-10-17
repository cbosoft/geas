#include "physics.hpp"
#include "collider.hpp"

Collider::Collider(Physics &owner)
  : owner(owner)
{
  // do nothing
}

Vec2 Collider::get_point_in_world(const Vec2 &point) const
{
  return this->owner.get_position().demote() + point;
}
