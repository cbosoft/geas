#pragma once

#include "../geas_object.hpp"
#include "camera_animator/camera_animator.hpp"

class Camera final : public GeasObject {
public:

    Camera(Transform *parent, Transform *target=nullptr);

    void update() override;

    void target(Transform *target);
    Transform *target() const;

    void area(const Vec4 &a);
    void fade_out() const;
    void fade_in() const;

private:
    Vec4 _area;
    Transform *_target;
};