#include "geas_object.hpp"

void GeasObject::update()
{
    if (this->physics) {
        const Vec2 &mom = this->physics->get_momentum();

        if (mom.x() > 0.0f) {
            this->contact_left(false);
        }
        else if (mom.x() < 0.0f) {
            this->contact_right(false);
        }

        if (mom.y() > 0.0f) {
            this->contact_bottom(false);
        }
        else if (mom.y() < 0.0f) {
            this->contact_top(false);
        }
    }
}