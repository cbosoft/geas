#include "camera.hpp"

Camera::Camera(float x, float y, float w, float h)
  : position({x, y}), size({w, h})
{
  // do nothing
}

void Camera::set_position(Vec2 position)
{
  this->position = position;
  this->_position3d = size.promote(0.0);
}

void Camera::set_size(Vec2 size)
{
  this->size = size;
  this->_size3d = size.promote(0.0);
}

const Vec2& Camera::get_position() const
{
  return this->position;
}

const Vec2& Camera::get_size() const
{
  return this->size;
}
