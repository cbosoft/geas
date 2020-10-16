#include "transform.hpp"

Transform::Transform()
  : _relative_position(Vec3(0.0))
    , _local_scale(Vec2(1.0))
    , _parent(nullptr)
{
  // do nothing
}

Transform::Transform(Transform *parent)
  :
    _relative_position(Vec3(0.0))
    , _local_scale(Vec2(1.0))
    , _parent(parent)
{
  // do nothing
}


// Getters
Vec3 Transform::absolute_position() const
{
  Vec3 abs_pos = this->relative_position();
  if (this->_parent) {
    abs_pos += this->_parent->absolute_position();
  }
  return abs_pos;
}

Vec3 Transform::relative_position() const
{
  return this->_relative_position;
}

Vec2 Transform::scale() const
{
  Vec2 scale = this->local_scale();
  if (this->_parent) {
    scale *= this->_parent->scale();
  }
  return scale;
}

Vec2 Transform::local_scale() const
{
  return this->_local_scale;
}

Transform *Transform::parent() const
{
  return this->_parent;
}

// Setters
void Transform::absolute_position(Vec3 abs)
{
  this->relative_position(abs - this->_parent->absolute_position());
}

void Transform::relative_position(Vec3 rel)
{
  this->_relative_position = rel;
}

void Transform::scale(Vec2 scale)
{
  this->local_scale(scale / this->_parent->scale());
}

void Transform::local_scale(Vec2 local_scale)
{
  this->_local_scale = local_scale;
}

void Transform::parent(Transform *parent)
{
  this->_parent = parent;
}
