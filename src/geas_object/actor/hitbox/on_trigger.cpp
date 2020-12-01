#include "hitbox.hpp"

void HitBox::on_trigger(GeasObject &with)
{
    if (&with != &this->get_owner()) {
        // TODO hurt (with)
    }
}