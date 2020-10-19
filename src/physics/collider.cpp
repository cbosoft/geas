#include "../geas_object/geas_object.hpp"
#include "collider.hpp"

Collider::Collider(GeasObject &parent)
  : Transform(parent)
{
}


/// Get shortest 2D distance between this collider and the other collider.
/// \param other the other collider.
/// \return Shortest distance between the two colliders.
Vec2 Collider::get_separation_between(const Collider *other) const
{
    std::pair<Vec2, Vec2> points = this->get_nearest(other);
    return points.first - points.second;
}


/// Calculate the normal vector (vector pointing away perpendicular) to the surface of the collider
/// \param at the point on the collider at which to calc the normal
/// \return the normal vector (2D)
Vec2 Collider::get_surface_normal(const Vec2 &at) const
{
    return Vec2({0.0, 1.0});
}