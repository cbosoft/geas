#include "../geas_object/geas_object.hpp"
#include "physics.hpp"

Physics::Physics(GeasObject &owner)
  : owner(owner)
    , collider(nullptr)
{
  this->set_mass(1.0);
  this->set_gravity(10000.0);
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
  this->gravity_scale = gravity;
}

Vec3 Physics::get_position() const
{
  return this->owner.transform->absolute_position();
}
void Physics::set_collider(Collider * collider)
{
  this->collider = collider;
}

bool Physics::interacts_with(const Physics *other) const
{
  (void) other;
  return true;
}
