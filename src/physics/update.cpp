#include <iostream>

#include "../geas_object/geas_object.hpp"
#include "../game/game.hpp"
#include "physics.hpp"

//static double ptime = 0.0;

void Physics::update()
{
  const std::list<Physics *> &entities = Physics::get_list();
  
  // TODO: order entities into cells?

  float dt = Game::singleton()->get_time_delta(), dt2 = dt*dt;

  for (Physics *a : entities) {
    Vec2 apos = a->get_position().demote();
    for (Physics *b : entities) {
      if (a == b)
        break;

      Vec2 bpos = b->get_position().demote();
      Vec2 f = Physics::get_force_between(apos, bpos);

      a->force_total = a->force_total + f;
      b->force_total = b->force_total - f;
    }
  }

  for (Physics *entity : entities) {
    Vec2 force = entity->force_total;
    force.y(force.y() - entity->gravity_scale);

    Vec2 delta_v = force * (dt2 * entity->_inv_mass);
    std::cerr << delta_v.x() << ", " << delta_v.y() << "  dt = " << dt << "  grav = " << entity->gravity_scale << std::endl;
    (*entity->owner.position) += delta_v;
  }
}
