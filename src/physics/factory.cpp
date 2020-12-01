#include <list>

#include "physics.hpp"

static std::list<Physics *> all_physics_entities;

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
        , _enabled(true)
{
    this->set_mass(1.0);
    this->set_gravity(1.0);

    all_physics_entities.push_back(this);
}

void Physics::remove_ref(Physics *ref)
{
  all_physics_entities.remove(ref);
}

const std::list<Physics *> &Physics::get_list()
{
  return all_physics_entities;
}
