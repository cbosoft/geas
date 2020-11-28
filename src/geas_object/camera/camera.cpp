#include "camera.hpp"

Camera::Camera(Transform *parent, Transform *target)
    : GeasObject(parent)
    , _area({-1024.0f, -1024.0f, 2048.0f, 2048.0f})
    , _target(target)
{
    // do nothing
    this->physics = Physics::create(*this);
    this->physics->set_fixed();
}
void Camera::target(Transform *target)
{
    this->_target = target;
}

Transform *Camera::target() const
{
    return this->_target;
}

void Camera::area(const Vec4 &a)
{
    this->_area = a;
}