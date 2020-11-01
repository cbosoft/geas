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


    const float bouncy = 0.5f;

    if (this->fixed || other->fixed) {

        Physics *fixedbody = this->fixed ? this : other;
        Physics *freebody = this->fixed ? other : this;

        if (freebody->collider->intersects(freebody->maybe_new_position, fixedbody->collider)) {
            freebody->maybe_new_position = freebody->owner.absolute_position() - (freebody->momentum * freebody->_inv_mass * bouncy).promote(0.0f);
        }

    }
    else {
        // TODO: momentum exchange
    }

}