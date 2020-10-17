#pragma once

#include <list>

#include "../vector/vector.hpp"
#include "collider.hpp"

class GeasObject;

// Class managing the physics of an object (mass, gravity, drag, collision)
class Physics {
  public:
    ~Physics();

    static Physics *create(GeasObject &owner);
    static void update();
    void set_mass(float mass);
    void set_gravity(float gravity);
    void set_collider(Collider *collider);

    Vec3 get_position() const;

    bool interacts_with(const Physics *other) const;

  private:
    static Vec2 get_force_between(const Vec2& a, const Vec2 &b);
    static const std::list<Physics *> &get_list();
    static void remove_ref(Physics *physics);

    Physics(GeasObject &owner);

    GeasObject &owner;
    float mass, _inv_mass;
    float gravity_scale;
    Vec2 force_total;
    Collider *collider;
};
