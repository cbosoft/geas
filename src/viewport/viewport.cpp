#include "viewport.hpp"

Viewport::Viewport()
  : size({100, 100}), position({0.0, 0.0})
{
  // do nothing
}

Viewport::~Viewport()
{
  // do nothing
}

Vec2 Viewport::scale_world_to_view(Vec2 world)
{
  Vec2 view = (world + position) / size;
  return view;
}

Viewport& Viewport::singleton()
{
  static Viewport m;
  return m;
}
