#include "physics.hpp"

Physics::Physics(GeasObject &owner)
  : owner(owner)
{
  // do nothing
}

Physics::~Physics()
{
  // do nothing
  Physics::remove_ref(this);
}
