#include <iostream>
#include "trigger.hpp"

Trigger::Trigger(GeasObject &owner, const Vec4 &rect)
    :   Physics(owner)
    ,   triggered(false)
    ,   triggered_cache(false)
{
    auto *r = new RectCollider(&owner, rect);
    this->set_collider(r);
    this->set_fixed(true);
}

void Trigger::trigger(GeasObject &with)
{
    this->triggered = true;
    if (this->is_newly_triggered()) {
        this->on_trigger(with);
    }
}

bool Trigger::is_newly_triggered() const
{
    return this->triggered != this->triggered_cache;
}

void Trigger::cache_value()
{
    this->triggered_cache = this->triggered;
    this->triggered = false;
}