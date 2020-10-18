#include "../util/debug.hpp"
#include "../util/formatter.hpp"

#include "physics.hpp"

static inline float simple_exp_potential(float dist)
{
  return std::exp(-5.0f*std::abs(dist));
}

Vec2 Physics::get_force_between(const Vec2 &a, const Vec2 &b)
{
  Vec2 dr = a - b;
  float dist = dr.magnitude();
  float denergy = simple_exp_potential(dist);
  Vec2 df = dr * denergy;

  debug_msg(Formatter() << df.magnitude() << "," << dr.to_string());
  return df;
}
