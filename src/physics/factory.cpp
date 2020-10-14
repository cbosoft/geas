#include <list>

#include "physics.hpp"

static std::list<Physics *> all_physics_entities;

Physics *Physics::create(GeasObject &owner)
{
  Physics *rv = new Physics(owner);
  all_physics_entities.push_back(rv);
  return rv;
}

void Physics::remove_ref(Physics *ref)
{
  all_physics_entities.remove(ref);
}

const std::list<Physics *> &Physics::get_list()
{
  return all_physics_entities;
}
