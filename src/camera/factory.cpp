#include <vector>
#include <map>

#include "../window/window.hpp"
#include "camera.hpp"

static std::vector<Camera *> cameras;
static std::map<std::string, Camera*> named_cameras;

Camera *Camera::create(std::string name)
{
  Window *win = Window::singleton();
  float w = win->get_w(), h = win->get_h();
  return Camera::create(0.0, 0.0, w/2, h/2, name);
}


Camera *Camera::create(float x, float y, float w, float h, std::string name)
{
  Camera *new_camera = new Camera(x, y, w, h);
  cameras.push_back(new_camera);

  if (!name.empty()) {
    named_cameras[name] = new_camera;
  }

  return new_camera;
}

Camera *Camera::main()
{
  if (cameras.size() < 1) {
    cameras.push_back(Camera::create());
  }

  return cameras[0];
}

Camera *Camera::by_name(std::string name)
{
  auto it = named_cameras.find(name);
  if (it != named_cameras.end()) {
    return it->second;
  }

  // TODO exception: camera not found
  return nullptr;
}

Camera *Camera::by_index(int index)
{
  if (cameras.size() > (unsigned int)index && index > 0) {
    return cameras[index];
  }

  // TODO exception: camera not found
  return nullptr;
}
