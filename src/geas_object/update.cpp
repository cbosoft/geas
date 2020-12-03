#include "geas_object.hpp"

void GeasObject::update()
{
    this->contact_mask = 0;
    // const float epsilon = 0.01f;
    // if (this->physics) {
    //     const Vec2 &mom = this->physics->get_momentum();

    //     if (mom.x() > epsilon) {
    //         this->contact_left(false);
    //     }
    //     else if (mom.x() < -epsilon) {
    //         this->contact_right(false);
    //     }

    //     if (mom.y() > epsilon) {
    //         this->contact_bottom(false);
    //     }
    //     else if (mom.y() < -epsilon) {
    //         this->contact_top(false);
    //     }
    // }
}
