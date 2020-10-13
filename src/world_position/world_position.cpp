#include "world_position.hpp"
#include "../camera/camera.hpp"

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
  return Camera::main()->world_to_window(position);
}
