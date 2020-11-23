#include "actor.hpp"

Actor::Actor(Transform *parent, float max_HP)
    : GeasObject(parent)
    , max_HP(max_HP)
{
    // do nothing
}
