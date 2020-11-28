#pragma once

#include "../geas_object.hpp"

class Camera final : public GeasObject {
public:

    Camera(Transform *parent, Transform *target=nullptr);

    void update() override;

    void target(Transform *target);
    Transform *target() const;

    void area(const Vec4 &a);

private:
    Vec4 _area;
    Transform *_target;
};