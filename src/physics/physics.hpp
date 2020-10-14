#pragma once

#include <list>

#include "../vector/vector.hpp"

class GeasObject;

// Class managing the physics of an object (mass, gravity, drag, collision)
class Physics {
  public:
    ~Physics();

    static Physics *create(GeasObject &owner);
    static void update();

  private:
    static const std::list<Physics *> &get_list();
    static void remove_ref(Physics *physics);

    Physics(GeasObject &owner);

    GeasObject &owner;
    float mass;
    Vec2 force_total;
};
