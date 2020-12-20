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
    r->size(Vec2({640.0f, 480.0f}));
    r->relative_position(Vec3({-320,-240,0}));
    this->renderable(r);

    auto *c = new CameraAnimator(*this);
    c->speed(0.5f);
    this->animator(c);

    this->set_transition("fade");
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

void Camera::fade_out(const std::string &transition_name) const
{
    if (!transition_name.empty())
        this->set_transition(transition_name);

    auto *animator = (CameraAnimator *)this->animator();
    if (animator) {
        animator->set_state("fade_out");
    }
}

void Camera::fade_in(const std::string &transition_name) const
{
    if (!transition_name.empty())
        this->set_transition(transition_name);

    auto *animator = (CameraAnimator *)this->animator();
    if (animator) {
        animator->set_state("fade_in");
    }
}

void Camera::set_transition(const std::string &transition_name) const
{
    std::string shade_texture_path = "assets/ui/transitions/" + transition_name + ".png";
    auto *r = this->renderable();
    r->set_texture(shade_texture_path);

    auto *c = this->animator();
    c->load_animations(shade_texture_path);
}
