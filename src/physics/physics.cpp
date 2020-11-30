#include "../geas_object/geas_object.hpp"
#include "physics.hpp"

Physics::Physics(GeasObject &owner)
  :
      drag(-0.1)
    , owner(owner)
    , mass(1.0f)
    , _inv_mass(1.0f)
    , gravity_scale(1.0f)
    , collider(nullptr)
    , material(Material::get_default())
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