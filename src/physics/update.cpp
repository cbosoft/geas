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

    // First loop: using the momentum of the entities, calculate their projected new position (Physics::maybe_new_position)
    for (Physics *entity : entities) {

        if (entity->fixed)
            continue;

        float raw_dv = entity->driving_accel * static_cast<float>(entity->driving_direction);
        float drag_dv = entity->momentum.x() * entity->drag;
        Vec2 accel({raw_dv + drag_dv, -entity->gravity_scale * entity->_inv_mass});
        entity->momentum += accel;
        Vec2 delta_r = entity->momentum*entity->_inv_mass;
        // Here "r" means position because physicists are weird (and p is momentum, and x would be misleading).

        entity->maybe_new_position = entity->owner.relative_position() + delta_r.promote(0.0);
    }


    // For all pairs of objects, check if the objects will interact. If they do, alter their projected new position accordingly.
    for (Physics *a : entities) {
        for (Physics *b : entities) {

          if (a == b)
              break;

          a->interact_with(b);

        }
    }

    // finally, set the projected new position for all entities.
    for (Physics *entity : entities) {

        if (entity->fixed)
            continue;

        entity->momentum = (entity->maybe_new_position - entity->get_position())*entity->mass;
        entity->owner.absolute_position(entity->maybe_new_position);
    }

  std::this_thread::sleep_for(std::chrono::microseconds(100));
}
