#include "camera.hpp"

Camera::Camera(Transform *parent, Transform *target)
    : GeasObject(parent)
    , _x_fixed(false)
    , _y_fixed(false)
    , _target(target)
{
    // do nothing
    this->physics = Physics::create(*this);
    this->physics->set_fixed();
}

void Camera::immobilise_horizontal(bool v)
{
    this->_x_fixed = v;
}

void Camera::immobilise_vertical(bool v)
{
    this->_y_fixed = v;
}

void Camera::target(Transform *target)
{
    this->_target = target;
}

Transform *Camera::target() const
{
    return this->_target;
}