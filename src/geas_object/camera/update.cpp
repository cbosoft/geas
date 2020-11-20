#include "camera.hpp"

void Camera::update()
{
    // move to target location

    if (_x_fixed && _y_fixed)
        return;

    if (!this->_target)
        return;

    Vec3 target_position = this->_target->absolute_position();
    Vec3 current_position = this->absolute_position();

    if (_x_fixed)
        target_position.x(current_position.y());

    if (_y_fixed)
        target_position.y(current_position.y());

    target_position.z(current_position.z());

    this->absolute_position(target_position);
}