#include <iostream>
#include <chrono>

#include "../globject/globject.hpp"
#include "../util/glerror.hpp"
#include "window.hpp"

static Window *singleton_ptr = nullptr;

Window *Window::singleton()
{
  if (singleton_ptr == nullptr) {
    // TODO: throw exception
    std::cerr << "singleton not yet init" << std::endl;
    exit(1);
  }

  return singleton_ptr;
}

Window::Window(int w, int h, std::string title)
  :
    _is_closed(false)
    , camera_position(Vec2({0.0, 0.0}))
    , camera_aperture_size(Vec2({float(w), float(h)}))
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

  singleton_ptr = this;
  std::cerr << "window singleto @ " << singleton_ptr << std::endl;

}

Window::~Window()
{
  glfwTerminate();
}

void Window::register_input_callback(key_callback func)
{
  glfwSetKeyCallback(this->glfw_window, func);
}

void Window::quit()
{
  glfwSetWindowShouldClose(this->glfw_window, true);
  this->_is_closed = true;
}

// void Window::run()
// {
// 
//   auto t0 = std::chrono::high_resolution_clock::now();
//   while (!glfwWindowShouldClose(this->glfw_window)) {
//     auto t1 = std::chrono::high_resolution_clock::now();
//     std::chrono::duration<float> fs = t1 - t0;
//     t0 = t1;
//     float dt = fs.count();
//     (void) dt;
//     // std::cout << "timeDelta: " << dt << "\n"
//     //   << "FPS: " << 1./dt << std::endl;
//     this->process_events();
// 
//     gl_error_check("Window::run()");
// 
//   }
// }

void Window::prepaint()
{
  gl_error_check("pre-Window::prepaint()");
  glClear(GL_COLOR_BUFFER_BIT);
  gl_error_check("pre-Window::prepaint()");
}

void Window::postpaint()
{
  // Swap front and back buffers
  glfwSwapBuffers(this->glfw_window);

  // GLFW events
  glfwPollEvents();

  if (glfwWindowShouldClose(this->glfw_window)) {
    this->_is_closed = true;
  }
}

bool Window::is_closed()
{
  return this->_is_closed;
}
