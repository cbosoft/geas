#pragma once

#include "../geas_object.hpp"

class Camera final : public GeasObject {
public:

    Camera(Transform *parent, Transform *target=nullptr);

    void immobilise_horizontal(bool v=true);
    void immobilise_vertical(bool v=true);
    void update() override;

    void target(Transform *target);
    Transform *target() const;

private:
    bool _x_fixed, _y_fixed;
    Transform *_target;
};