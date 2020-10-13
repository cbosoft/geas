#include "window.hpp"

Vec2 Window::world_to_win(Vec2 position)
{
  Vec2 relpos_world = position - this->camera_position;
  Vec2 relpos_cam = relpos_world / camera_aperture_size;
  return relpos_cam;
}

Vec3 Window::world_to_win(Vec3 position)
{
  Vec3 campos3d = Vec3({camera_position.x(), camera_position.y(), 0.0});
  Vec3 camsize3d = Vec3({camera_aperture_size.x(), camera_aperture_size.y(), 1.0});
  Vec3 relpos_world = position - campos3d;
  Vec3 relpos_cam = relpos_world / camsize3d;
  return relpos_cam;
}
