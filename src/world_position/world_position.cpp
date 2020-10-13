#include "world_position.hpp"
#include "../window/window.hpp"

WorldPosition::WorldPosition(float x, float y, float z)
  : WorldPosition(Vec3({x, y, z}))
{
  // do nothing
}

WorldPosition::WorldPosition(Vec3 position)
  : position(position)
{
  // do nothing
}

Vec3 WorldPosition::in_window_coords() const
{
  Window &win = Window::singleton();
  return win.world_to_win(position);
}
