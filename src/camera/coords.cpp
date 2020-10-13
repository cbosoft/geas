#include "camera.hpp"


Vec2 Camera::world_to_window(Vec2 position)
{
  Vec2 relpos_world = position - this->position;
  Vec2 relpos_cam = relpos_world / this->size;
  return relpos_cam;
}

Vec3 Camera::world_to_window(Vec3 position)
{
  Vec3 relpos_world = position - this->_position3d;
  Vec3 relpos_cam = relpos_world / this->_size3d;
  return relpos_cam;
}

Vec2 Camera::window_to_world(Vec2 position)
{
  Vec2 relpos_world = position * this->size;
  Vec2 worldpos = relpos_world + this->position;
  return worldpos;
}

Vec3 Camera::window_to_world(Vec3 position)
{
  Vec3 relpos_world = position * this->_size3d;
  Vec3 worldpos = relpos_world + this->_position3d;
  return worldpos;
}
