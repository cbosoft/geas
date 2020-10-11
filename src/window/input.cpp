#include "window.hpp"

void Window::process_input(int key, int scancode, int action, int mods)
{
  (void) scancode;
  (void) action;
  (void) mods;

  switch (key)
  {
    case GLFW_KEY_ESCAPE:
      glfwSetWindowShouldClose(this->glfw_window, true);
      break;

    default:
      break;
  }
}
