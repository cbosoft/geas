#include <iostream>
#include <chrono>

#include "../globject/globject.hpp"
#include "../util/glerror.hpp"
#include "window.hpp"

Window &Window::singleton(int w, int h, std::string title)
{
  static Window win(w, h, title);
  return win;
}

Window &Window::singleton()
{
  return Window::singleton(0, 0, "null");
}

static void window_input_callback(GLFWwindow *win_ptr, int key, int scancode, int action, int mods)
{
  (void)win_ptr;
  Window::singleton().process_input(key, scancode, action, mods);
}

Window::Window(int w, int h, std::string title)
  : camera_position(Vec2({0.0, 0.0})), camera_aperture_size(Vec2({float(w), float(h)}))
{
  if (!glfwInit()) {
    // could not init glfw!
    std::cerr << "error initialising GLFW" << std::endl;
    exit(1);
  }
  else {
    std::cout << "GLFW " << glfwGetVersionString() << " initialised" << std::endl;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  glfw_window = glfwCreateWindow(w, h, title.c_str(), nullptr, nullptr);
  if (!glfw_window)
  {
    glfwTerminate();
    std::cerr << "error creating window" << std::endl;
    exit(1);
  }

  glfwMakeContextCurrent(glfw_window);

  GLenum res;
  if ((res = glewInit()) != GLEW_OK) {
    std::cerr << "error initialising GLEW:" << glewGetErrorString(res) << std::endl;
    exit(1);
  }
  else {
    std::cout << "GLEW " << glewGetString(GLEW_VERSION) << " initialised" << std::endl;
  }

  glfwSetKeyCallback(glfw_window, window_input_callback);

}

Window::~Window()
{
  glfwTerminate();
}

void Window::run()
{

  auto t0 = std::chrono::high_resolution_clock::now();
  while (!glfwWindowShouldClose(this->glfw_window)) {
    auto t1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> fs = t1 - t0;
    t0 = t1;
    float dt = fs.count();
    (void) dt;
    // std::cout << "timeDelta: " << dt << "\n"
    //   << "FPS: " << 1./dt << std::endl;
    this->process_events();

    gl_error_check("Window::run()");

  }
}

void Window::process_events()
{

  glClear(GL_COLOR_BUFFER_BIT);

  // window events
  std::list<GLObject *> remaining_objects;
  for (auto object : this->objects) {
    if (object->draw(*this)) {
      delete object;
    }
    else {
      remaining_objects.push_back(object);
    }
  }
  this->objects = remaining_objects;

  // Swap front and back buffers
  glfwSwapBuffers(this->glfw_window);

  // GLFW events
  glfwPollEvents();
}

void Window::push_object(GLObject *object)
{
  this->objects.push_back(object);
}
