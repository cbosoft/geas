#include "collider.hpp"


RectCollider::RectCollider(GeasObject &owner, Vec2 bl_offset, Vec2 size)
  : Collider(owner)
    , size(size)
{
  this->relative_position(bl_offset.promote(0.0f));
}

RectCollider::~RectCollider()
{
  // do nothing
}


/// Get the centre point of the rectangle, in absolute coordinates
/// \return the centre of the rectangle
Vec2 RectCollider::get_centre() const
{
  Vec2 bl = this->absolute_position();
  return bl + this->size*0.5;
}


/// Get the absolute (world) positions of the four corners of this rectangle.
/// \return list of Vec2 positions
std::list<Vec2> RectCollider::get_corners() const
{
    std::list<Vec2> corners;
    Vec2 bl = this->absolute_position();
    corners.push_back(bl + this->size);
    corners.push_back(bl + Vec2({this->size.x(), 0.0}) );
    corners.push_back(bl);
    corners.push_back(bl + Vec2({0.0, this->size.y()}) );
    return corners;
}


/// Get the point on the rectangle nearest to the other point p.
/// \param p
/// \return Nearest point to p
Vec2 RectCollider::get_nearest(const Vec2 &p) const
{
  //std::list<Vec2> corners = this->get_corners();

  // TODO: get nearest point on the collider to the point p
  (void) p;
  
  return this->get_centre();
}


/// Get nearest points on this collider to collider other
/// \param other
/// \return pair of position on *this* surface, and position on *other* surface
std::pair<Vec2, Vec2> RectCollider::get_nearest(const Collider *other) const
{
    // TODO
    return std::make_pair(this->get_centre(), other->get_centre());
}


/// Calculate the normal vector (vector pointing away perpendicular) to the surface of the collider
/// \param at the point on the collider at which to calc the normal
/// \return the normal vector (2D)
Vec2 RectCollider::get_surface_normal(const Vec2 &at) const
{
    // TODO: implement function
    (void) at; // appease linter
    return Vec2({0.0, 1.0});
}
