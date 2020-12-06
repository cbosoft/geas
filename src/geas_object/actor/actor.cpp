#include "actor.hpp"

Actor::Actor(Transform *parent, float max_HP)
    : GeasObject(parent)
    , HP(max_HP)
    , max_HP(max_HP)
    , melee_hitbox(nullptr)
{
    // do nothing
}

HitBox *Actor::get_melee_hitbox() const
{
    return this->melee_hitbox;
}

void Actor::set_melee_hitbox(HitBox *hitbox)
{
    this->melee_hitbox = hitbox;
}

bool Actor::is_dead() const
{
    return this->HP <= 0.0f;
}

float Actor::get_HP() const
{
    return this->HP;
}

void Actor::hurt(float dam)
{
    this->HP -= dam;
}
