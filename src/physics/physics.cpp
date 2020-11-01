#include "../geas_object/geas_object.hpp"
#include "physics.hpp"

Physics::Physics(GeasObject &owner)
  : owner(owner)
    , collider(nullptr)
    , direction_constraints_mask(0)
{
  this->set_mass(1.0);
  this->set_gravity(1.0);
}

Physics::~Physics()
{
  // do nothing
  Physics::remove_ref(this);
}

void Physics::set_mass(float mass)
{
  this->mass = mass;
  this->_inv_mass = 1.0f/mass;
}

void Physics::set_gravity(float gravity)
{
  this->gravity_scale = gravity*Physics::global_gravity_scale;
}

Vec3 Physics::get_position() const
{
  return this->owner.absolute_position();
}
void Physics::set_collider(RectCollider * collider)
{
  this->collider = collider;
}

void Physics::set_fixed(bool is_fixed)
{
    this->fixed = is_fixed;
}
