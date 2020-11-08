#include <iostream>

#include "../geas_object/geas_object.hpp"
#include "../util/formatter.hpp"
#include "../util/debug.hpp"

#include "physics.hpp"

/// Calculate the resulting momentum of a free body, after interacting with a fixed body's surface.
/// \param incoming_momentum Momentum of the free body which interacts with the fixed.
/// \param surface_normal_unit The unit vector indicating the direction perpendicular (normal) to the fixed object's surface.
/// \return The resulting momentum of the free body after interaction.
Vec2 fixed_body_momentum_transfer(const Vec2 &incoming_momentum, const Vec2 &surface_normal_unit)
{
    // TODO
    // interaction with a fixed body. resulting momentum vector component normal to the surface is flipped, while
    // tangent components are reflected across the normal.

    // appease linter
    (void) incoming_momentum;
    (void) surface_normal_unit;

    const float bouncy = 0.15;

    float mag = incoming_momentum.magnitude();
    Vec2 resulting_momentum = mag*bouncy*surface_normal_unit;

    debug_msg(surface_normal_unit.to_string());

    return resulting_momentum;
}


/// One physics object interacting with another. Momentum of either physics object can be altered in this step.
/// \param other The other physics object which will interact with this one.
void Physics::interact_with(Physics *other)
{

    if (this->fixed && other->fixed)
        return;

    if (!(this->collider && other->collider))
        return;


    const float elasticity = (this->material->elasticity() + other->material->elasticity()) * 0.5f;

    if (this->fixed || other->fixed) {

        Physics *fixedbody = this->fixed ? this : other;
        Physics *freebody = this->fixed ? other : this;

        const Vec2 cp = this->get_position();
        const Vec2 dr = freebody->maybe_new_position.demote() - cp;
        Vec2 drx_vec = Vec2({dr.x(), 0.0f});
        Vec2 dry_vec = Vec2({0.0f, dr.y()});

        if ((freebody->collider->intersects(drx_vec, fixedbody->collider)) || (fixedbody->collider->intersects(drx_vec*-1.0, freebody->collider))) {
            float npx = freebody->owner.absolute_position().x() - (freebody->momentum.x() * freebody->_inv_mass * elasticity);
            freebody->maybe_new_position.x(npx);

            if (dr.x() > 0.0f) {
                freebody->owner.contact_right(true);
                fixedbody->owner.contact_left(true);
            }
            else {
                freebody->owner.contact_left(true);
                fixedbody->owner.contact_right(true);
            }
        }

        if ((freebody->collider->intersects(dry_vec, fixedbody->collider)) || (fixedbody->collider->intersects(dry_vec*-1.0, freebody->collider))) {
            float npy = freebody->owner.absolute_position().y() - (freebody->momentum.y() * freebody->_inv_mass * elasticity);
            freebody->maybe_new_position.y(npy);

            if (dr.y() > 0.0f) {
                freebody->owner.contact_top(true);
                fixedbody->owner.contact_bottom(true);
            }
            else {
                freebody->owner.contact_bottom(true);
                fixedbody->owner.contact_top(true);
            }
        }

    }
    else {
        // TODO: momentum exchange
    }

}