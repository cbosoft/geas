#pragma once

#include "../vector/vector.hpp"

class PhysicsObject {

  public:
    PhysicsObject();

  private:

    Vec3 position; /* in world coords, NOT SCREEN */
    Vec3 velocity;
    float mass;
};
