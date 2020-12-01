#include "../geas_object/geas_object.hpp"
#include "physics.hpp"

// constructor in "factory.cpp"

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
  this->gravity_scale = gravity*Physics::global_gravity_scale();
}

Vec3 Physics::get_position() const
{
  return this->owner.absolute_position();
}

const Vec2 &Physics::get_momentum() const
{
    return this->momentum;
}

void Physics::set_collider(RectCollider *c)
{
  this->collider = c;
}

void Physics::set_collider(const Vec4 &rect)
{
    this->collider = new RectCollider(&this->owner, rect);
}

void Physics::set_fixed(bool is_fixed)
{
    this->fixed = is_fixed;
}

void Physics::add_impulse(const Vec2 &force)
{
    this->force_total += force;
}


RectCollider *Physics::get_collider() const
{
    return this->collider;
}