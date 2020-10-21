#include "../geas_object/geas_object.hpp"
#include "physics.hpp"

Vec2 fixed_body_momentum_transfer(const Vec2 &incoming_momentum, const Vec2 &surface_normal_unit)
{
    // TODO
    // interaction with a fixed body. resulting momentum vector component normal to the surface is flipped, while
    // tangent components are reflected across the normal.

    // appease linter
    (void) incoming_momentum;
    (void) surface_normal_unit;

    return Vec2(0.0);
}

void Physics::interact_with(Physics *other)
{
    // if both objects are fixed, nothing to do!
    if (this->fixed && other->fixed)
        return;

    // Get distance between other collider's surface and this surface
    std::pair<Vec2, Vec2> surface_positions = other->collider->get_nearest(this->collider);
    Vec2 other_surface_pos = surface_positions.first;
    Vec2 this_surface_pos = surface_positions.second;
    Vec2 dr = this_surface_pos - other_surface_pos;

    // # Is touching?
    // Check if the separation is smaller than a threshold, if so the objects are in contact threshold needs to be small
    // such that the objects enclosing speed (speed at which the distance between them is decreasing, speed of one obj
    // relative to other) times the timedelta is greater than the threshold. This is to prevent ghost reflections
    // wherein an object "rattles" on collision.

    const float threshold  = 1e-2f;
    float dist = dr.magnitude();
    if (dist < threshold) {
        // touching!
        // if both objects are free (non-fixed) then transfer momentum between the objects (rotation is ignored)
        // if one object is fixed then the other object will have its momentum reflected
        // the material properties of the entities will inform how efficient the momentum transfer is (i.e. the degree
        // of elasticity.

        // TODO adapt that dude's thesis to work here (collision response method) https://en.wikipedia.org/wiki/Collision_response
        if (this->fixed) {
            other->momentum = fixed_body_momentum_transfer(other->momentum, this->collider->get_surface_normal(other_surface_pos));
        }
        else if (other->fixed) {
            this->momentum = fixed_body_momentum_transfer(this->momentum, other->collider->get_surface_normal(this_surface_pos));
        }
        else {
            // momentum transfers from one object to another.
            // no inertia yet, just simple momentum transfer (think Newton's cradle)
            // inertia can come later

            Vec2 momentumOther = other->momentum;
            other->momentum = this->momentum;
            this->momentum = other->momentum;
            // TODO: friction

        }


    }

}