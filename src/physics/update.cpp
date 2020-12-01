#include <iostream>
#include <thread>
#include <chrono>

#include "../geas_object/geas_object.hpp"
#include "../game/game.hpp"
#include "../util/debug.hpp"
#include "../util/formatter.hpp"
#include "physics.hpp"
#include "trigger/trigger.hpp"

//static double ptime = 0.0;
static std::chrono::time_point<std::chrono::system_clock> t0;
static bool t0set = false;

void Physics::update()
{
    float dt = Physics::time_scale();

    if (!t0set) {
        t0 = std::chrono::system_clock::now();
        t0set = true;
    }
    const std::list<Physics *> &entities = Physics::get_list();
    std::list<Physics *> non_fixed_entities;

    // First loop: using the momentum of the entities, calculate their projected new position (Physics::maybe_new_position)
    for (Physics *entity : entities) {

        if (!entity->owner.is_enabled())
            continue;

        if (!entity->is_enabled())
            continue;

        entity->owner.update();

        if (entity->is_trigger()) {
            auto *t = dynamic_cast<Trigger *>(entity);
            t->cache_value();
        }

        if (entity->fixed)
            continue;

        float drag_dv = entity->momentum.x() * entity->drag;
        Vec2 accel({
            drag_dv + entity->force_total.x()*entity->_inv_mass,
            (entity->force_total.y() - entity->gravity_scale)*entity->_inv_mass
        });
        entity->force_total.zero();
        entity->momentum += accel*dt;
        Vec2 delta_r = entity->momentum*entity->_inv_mass*dt;
        // Here "r" means position because physicists are weird (and p is momentum, and x would be misleading).

        entity->maybe_new_position = entity->owner.relative_position() + delta_r.promote(0.0);
        non_fixed_entities.push_back(entity);
    }


    // For all pairs of objects, check if the objects will interact. If they do, alter their projected new position accordingly.
    for (Physics *a : non_fixed_entities) {

        Vec3 apos = a->get_position();
        for (Physics *b : entities) {

          if (a == b)
              break;

            if (!b->is_enabled() || !b->owner.is_enabled())
                continue;

          Vec3 dr = apos - b->get_position();
          float dist = dr.magnitude();
          if (dist > Physics::interaction_threshold())
              continue;

          // Expensive!
          a->interact_with(b);

        }
    }

    // finally, set the projected new position for all entities.
    for (Physics *entity : entities) {

        if (entity->fixed)
            continue;

        entity->momentum = (entity->maybe_new_position - entity->get_position())*entity->mass/dt;
        entity->owner.absolute_position(entity->maybe_new_position);
    }

    std::chrono::time_point<std::chrono::system_clock> t1 = std::chrono::system_clock::now();
    int dt_us = std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count();

    int w = Physics::update_period_us() - dt_us;
    if (w < 0) w = 0;

    //std::cerr << dt_us << " us, w = " << w << std::endl;
    std::this_thread::sleep_for(std::chrono::microseconds(w));
    t0 = std::chrono::system_clock::now();
}
