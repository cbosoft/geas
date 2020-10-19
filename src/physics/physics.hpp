#pragma once

#include <list>

#include "../vector/vector.hpp"
#include "collider.hpp"

class GeasObject;

// Class managing the physics of an object (mass, gravity, drag, collision)
class Physics {
  public:
    friend class Collider;

    ~Physics();

    static Physics *create(GeasObject &owner);
    static void update();
    void set_mass(float mass);
    void set_gravity(float gravity);
    void set_collider(Collider *collider);
    void set_fixed(bool is_fixed=true);

    Vec3 get_position() const;

  private:
    void interact_with(Physics *other);
    static const std::list<Physics *> &get_list();
    static void remove_ref(Physics *physics);

    Physics(GeasObject &owner);

    bool fixed{false};
    GeasObject &owner;
    float mass, _inv_mass;
    float gravity_scale;
    Vec2 momentum;
    Vec2 force_total;
    Collider *collider;
};
