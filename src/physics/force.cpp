#include "../util/debug.hpp"
#include "../util/formatter.hpp"

#include "physics.hpp"

static float simple_exp_potential(float dist)
{
  return std::exp(-5.0*std::abs(dist));
}

Vec2 Physics::get_force_between(const Vec2 &a, const Vec2 &b)
{
  Vec2 dr = a - b;
  Vec2 df = Vec2({
    simple_exp_potential(dr.x()),
    simple_exp_potential(dr.y()),
  });

  debug_msg(Formatter() << "dr=" << dr.to_string() << " -> df=" << df.to_string());
  return df;
}
