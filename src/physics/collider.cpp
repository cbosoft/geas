#include "../geas_object/geas_object.hpp"
#include "physics.hpp"
#include "collider.hpp"

Collider::Collider(Physics &owner)
  : Transform(&owner.owner)
  , owner(owner)
{
  // do nothing
}


/// Get shortest 2D distance between this collider and the other collider.
/// \param other the other collider.
/// \return Shortest distance between the two colliders.
Vec2 Collider::get_separation_between(const Collider *other) const
{
    std::pair<Vec2, Vec2> points = this->get_nearest(other);
    return points.first - points.second;
}