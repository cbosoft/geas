#include "physics.hpp"

void Physics::update()
{
  const std::list<Physics *> &entities = Physics::get_list();
  
  // TODO: order entities into cells?

  for (Physics *entity : entities) {
    (void) entity;

    // TODO
    // set force on entity from all other entities
    // use resulting unbalanced force to obtain the acceleration: a = f/m
    // then simply integrate to obtain velocity change, and then position change
    // a = f/m
    // dv = a*dt
    // v = v + dv
    // dr = v*dt
    // above integration scheme is over simplified (plain euler method)
    // could definitely be improved
  }
}
