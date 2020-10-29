#include <iostream>
#include <thread>
#include <chrono>

#include "../geas_object/geas_object.hpp"
#include "../game/game.hpp"
#include "../util/debug.hpp"
#include "../util/formatter.hpp"
#include "physics.hpp"

//static double ptime = 0.0;

void Physics::update()
{
  const std::list<Physics *> &entities = Physics::get_list();
  
  // TODO: order entities into cells?

  float dt = Game::singleton()->get_time_delta();

  for (Physics *a : entities) {
    for (Physics *b : entities) {

      if (a == b)
        break;

      a->interact_with(b);

    }
  }

  for (Physics *entity : entities) {

      if (entity->fixed)
          continue;

      Vec2 accel({0.0f, -entity->gravity_scale * entity->_inv_mass});
      entity->momentum += accel*dt;
      Vec2 vel = entity->momentum*entity->_inv_mass;

      // Here "r" means position because physicists are weird (and p is momentum, and x would be misleading).
      Vec2 delta_r = vel * dt;

      entity->owner.relative_position(entity->owner.relative_position() + delta_r.promote(0.0));
  }

  std::this_thread::sleep_for(std::chrono::microseconds(100));
}
