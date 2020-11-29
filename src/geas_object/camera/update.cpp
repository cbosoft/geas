#include "camera.hpp"

void Camera::update()
{

    if (!this->_target)
        return;

    // move to target location
    Vec3 target_position = this->_target->absolute_position();

    if (target_position.x() > this->_area.x() + this->_area.w()) {
        target_position.x(this->_area.x() + this->_area.w());
    }
    else if (target_position.x() < this->_area.x()) {
        target_position.x(this->_area.x());
    }

    if (target_position.y() > this->_area.y() + this->_area.h()) {
        target_position.y(this->_area.y() + this->_area.h());
    }
    else if (target_position.y() < this->_area.y()) {
        target_position.y(this->_area.y());
    }

    Vec3 current_position = this->absolute_position();
    target_position.z(current_position.z());

    const float smoothing = 0.98f;
    Vec3 result = current_position * smoothing + target_position * (1.0f - smoothing);
    this->absolute_position(result);
}