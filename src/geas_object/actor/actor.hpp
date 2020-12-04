#pragma once

#include "../geas_object.hpp"
#include "hitbox/hitbox.hpp"

class Actor : public GeasObject {
public:
    Actor(Transform *parent, float max_HP);

    float HP, max_HP;

    virtual void hurt(float dam);
    bool is_dead() const;
    float get_HP() const;

    HitBox *get_melee_hitbox() const;
    void set_melee_hitbox(HitBox *hitbox);

    virtual void move(int dir) =0;
    virtual void jump() =0;
    virtual void crouch(bool v) =0;


private:

    HitBox *melee_hitbox;

};