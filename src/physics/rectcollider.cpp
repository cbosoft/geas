#include <vector>
#include "../util/exception.hpp"
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
  
  return this->absolute_position();
}


/// Get nearest points on this collider to collider other
/// \param other
/// \return pair of position on *this* surface, and position on *other* surface
std::pair<Vec2, Vec2> RectCollider::get_nearest(const Collider *other) const
{
    // TODO
    // draw line from this centre to other centre
    Vec2 dr = other->get_centre() - this->get_centre();

    static Vec2 vert({0.0f, 1.0f});
    const float a = std::abs(dr.dot(vert)/dr.magnitude());
    float theta = std::acos(a);
    if (dr.x() > 0.0f) {
        if (dr.y() > 0.0) {
            // angle is acute
            // do nothing
        }
        else {
            // pos x, neg y: angle is obtuse
            theta += M_PI_2;
        }
    }
    else {
        if (dr.y() > 0.0) {
            // neg x, pos y: angle is between 3/2 pi and 2 pi
            theta += M_PI - M_PI_4;
        }
        else {
            // neg x, neg y: angle is between pi and 3/2 pi
            theta += M_PI;
        }
    }

    // TODO calculate cross over of c2c vec and side
    if ((theta >= M_PI_4) && (theta < M_PI - M_PI_4)) {
        // right
    }
    else if ((theta >= M_PI - M_PI_4) && (theta < M_PI + M_PI_4)) {
        // down
    }
    else if ((theta >= M_PI + M_PI_4) && (theta < M_2_PI - M_PI_4)) {
        // left
    }
    else /*if ((theta >= M_2_PI - M_PI_4) || (theta < M_PI_4))*/ {
        // up
    }


    return std::make_pair(this->absolute_position(), other->absolute_position());
}


/// Calculate the normal vector (vector pointing away perpendicular) to the surface of the collider
/// \param at the point on the collider at which to calc the normal
/// \return the normal vector (2D)
Vec2 RectCollider::get_surface_normal(const Vec2 &at) const
{
    auto corners = this->get_corners();
    corners.push_back(corners.front());
    std::list<Vec2> normals{
        Vec2({ 1.0,  0.0}),
        Vec2({ 0.0, -1.0}),
        Vec2({ -1.0,  0.0}),
        Vec2({ 0.0,  1.0})
    };

    auto corner = corners.begin(), next_corner = corner++, normal = normals.begin();

    for (;next_corner != corners.end();corner++, next_corner++, normal++) {

        if (at.coincident(*corner, *next_corner)) {
            return *normal;
        }

    }

    throw PositionError(Formatter() << "RectCollider::get_surface_normal(at) -> position " << at.to_string() << " is not on the rectangle.");
}
