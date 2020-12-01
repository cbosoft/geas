#pragma once

#include "../geas_object.hpp"
#include "hitbox/hitbox.hpp"

class Actor : public GeasObject {
public:
    Actor(Transform *parent, float max_HP);

    float HP, max_HP;

    virtual void hurt(float v) =0;
    bool is_dead() const;

    HitBox *get_melee_hitbox() const;
    void set_melee_hitbox(HitBox *hitbox);

private:

    HitBox *melee_hitbox;

};