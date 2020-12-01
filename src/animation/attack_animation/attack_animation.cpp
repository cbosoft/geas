#include "attack_animation.hpp"

AttackAnimation::AttackAnimation(Actor &owner, const Vec2 &position, float distance, unsigned int len)
    :   Animation("attack", 0, 1)
    ,   owner(owner)
    ,   len(len)
    ,   i(0)
{
    auto flen = static_cast<float>(len);
    float dy = distance / flen;
    Vec2 p = position;
    for (unsigned int i = 0; i < len; i++) {
        p.y(p.y() - dy);
        positions.push_back(p);
    }
}