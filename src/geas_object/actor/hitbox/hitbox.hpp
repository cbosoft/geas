#pragma once

#include "../../../physics/trigger/trigger.hpp"

class HitBox : public Trigger {
public:
    HitBox(GeasObject &owner, const Vec4 &rect);

    void on_trigger(GeasObject &with) override;

};