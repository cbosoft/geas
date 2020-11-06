#pragma once

#include <list>
#include <chrono>

#include "../vector/vector.hpp"
#include "collision/rectcollider.hpp"

class GeasObject;

enum DirectionalConstraint {DC_None, DC_Up, DC_Down, DC_Right, DC_Left};
typedef unsigned int bitmask_t;

// Class managing the physics of an object (mass, gravity, drag, collision)
class Physics {
  public:
    friend class RectCollider;

    ~Physics();

    static Physics *create(GeasObject &owner);
    static void update();
    void set_mass(float mass);
    void set_gravity(float gravity);
    void set_collider(RectCollider *collider);
    void set_fixed(bool is_fixed=true);

    Vec3 get_position() const;
    const Vec2 &get_momentum() const;

    void add_constraint(DirectionalConstraint constraint);
    void add_constraint(bitmask_t mask);
    void remove_constraint(DirectionalConstraint constraint);
    void remove_constraint(bitmask_t mask);
    [[nodiscard]] bool check_constraint(DirectionalConstraint constraint) const;
    [[nodiscard]] bool check_constraint(bitmask_t mask) const;

    void add_impulse(const Vec2 &force);


    static float global_gravity_scale();
    static void global_gravity_scale(float v);

    static int update_period_us();
    static void update_period_us(int v);
    static void update_rate_hz(int v);

    static float time_scale();
    static void time_scale(float v);

    float drag;

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
    RectCollider *collider;
    bitmask_t direction_constraints_mask;
    Vec3 maybe_new_position;

};
