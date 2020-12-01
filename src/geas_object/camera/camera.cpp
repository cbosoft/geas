#include <iostream>
#include "camera.hpp"

Camera::Camera(Transform *parent, Transform *target)
    : GeasObject(parent)
    , _area({-1024.0f, -1024.0f, 2048.0f, 2048.0f})
    , _target(target)
{
    // do nothing
    this->physics = new Physics(*this);
    this->physics->set_fixed();

    auto *r = new Renderable(this);
    r->set_texture("assets/textures/camera_shade.png");
    r->size(Vec2({640.0f, 480.0f}));
    this->renderable(r);

    auto *c = new CameraAnimator(*this);
    c->load_animations("assets/textures/camera_shade.png");
    c->speed(0.5f);
    this->animator(c);
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

void Camera::fade_out() const
{
    auto *animator = (CameraAnimator *)this->animator();
    if (animator) {
        animator->set_state("fade_out");
    }
}

void Camera::fade_in() const
{
    auto *animator = (CameraAnimator *)this->animator();
    if (animator) {
        animator->set_state("fade_in");
    }
}
