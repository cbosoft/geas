#pragma once

#include "../geas_object.hpp"

class Actor : public GeasObject {
public:
    Actor(Transform *parent, float max_HP);
    float HP, max_HP;

    virtual void hurt(float v) =0;
    bool is_dead() const;

};