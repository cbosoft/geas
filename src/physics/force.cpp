#include "physics.hpp"

static float simple_exp_potential(float dist)
{
  return std::exp(-5.0*dist);
}

Vec2 Physics::get_force_between(const Vec2 &a, const Vec2 &b)
{
  return Vec2({
      simple_exp_potential(std::abs(a.x() - b.x())),
      simple_exp_potential(std::abs(a.y() - b.y()))
  });
}
