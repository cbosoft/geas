#include <vector>
#include "../../util/exception.hpp"
#include "../../geas_object/geas_object.hpp"
#include "rectcollider.hpp"


RectCollider::RectCollider(GeasObject *owner, const Vec4 &rect)
        : Transform(owner)
        , tr(this)
        , br(this)
        , bl(this)
        , tl(this)
{
    Vec2 bl_offset({rect.x(), rect.y()});
    this->size.x(rect.get(2));
    this->size.y(rect.get(3));
    this->relative_position(bl_offset.promote(0.0f));

    this->tr.relative_position(size.promote(0.0f));
    this->br.relative_position(Vec3({size.x(), 0.0f, 0.0f}));
    this->tl.relative_position(Vec3({0.0f, size.x(), 0.0f}));
}

RectCollider::RectCollider(GeasObject *owner, const Vec2 &bl_offset, const Vec2 &size)
  : Transform(owner)
    , size(size)
    , tr(this)
    , br(this)
    , bl(this)
    , tl(this)
{
  this->relative_position(bl_offset.promote(0.0f));

  this->tr.relative_position(size.promote(0.0f));
  this->br.relative_position(Vec3({size.x(), 0.0f, 0.0f}));
  this->tl.relative_position(Vec3({0.0f, size.x(), 0.0f}));
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
    std::list<Vec2> corners({
        this->tr.absolute_position(),
        this->br.absolute_position(),
        this->bl.absolute_position(),
        this->tl.absolute_position()
    });
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
std::pair<Vec2, Vec2> RectCollider::get_nearest(const RectCollider *other) const
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
    Vec2 thispos = this->absolute_position(), otherpos = other->absolute_position();
    if ((theta >= M_PI_4) && (theta < M_PI - M_PI_4)) {
        // right on this, left on other
        thispos = thispos + this->size*Vec2({1.0,0.5});
        otherpos = otherpos + Vec2({0.0f, this->size.y()*0.5f});
    }
    else if ((theta >= M_PI - M_PI_4) && (theta < M_PI + M_PI_4)) {
        // bottom on this, top on other
        thispos = thispos + Vec2({this->size.x()*0.5f, 0.0f});
        otherpos = otherpos + this->size*Vec2({0.5f,1.0f});
    }
    else if ((theta >= M_PI + M_PI_4) && (theta < M_2_PI - M_PI_4)) {
        // left on this, right on other
        otherpos = otherpos + this->size*Vec2({1.0,0.5});
        thispos = thispos + Vec2({0.0f, this->size.y()*0.5f});
    }
    else /*if ((theta >= M_2_PI - M_PI_4) || (theta < M_PI_4))*/ {
        // top on this, bottom on other
        otherpos = otherpos + Vec2({this->size.x()*0.5f, 0.0f});
        thispos = thispos + this->size*Vec2({1.0,0.5});
    }


    return std::make_pair(thispos, otherpos);
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

        if (at.coincident(*corner, *next_corner, 0.01)) {
            return *normal;
        }

    }

    throw PositionError(Formatter() << "RectCollider::get_surface_normal(at) -> position " << at.to_string() << " is not on the rectangle. " << this->tr.absolute_position().to_string());
}



bool RectCollider::intersects(const Vec2 &dr, const RectCollider *other) const
{
    auto corners = this->get_corners();
    for (const auto &corner : corners) {
        Vec2 ppos = corner + dr;
        if (other->contains_point(ppos)) {
            return true;
        }
    }

    return false;
}


bool RectCollider::contains_point(const Vec2 &pt) const
{
    Vec2 blpt = this->bl.absolute_position();

    return (
            (pt.x() > blpt.x()) &&
            (pt.x() <= blpt.x() + this->size.x()) &&
            (pt.y() > blpt.y()) &&
            (pt.y() <= blpt.y() + this->size.y())
        );
}

















