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

#ifdef DEBUG

void APIENTRY glDebugOutput(GLenum source,
                            GLenum type,
                            unsigned int id,
                            GLenum severity,
                            GLsizei length,
                            const char *message,
                            const void *userParam)
{
  (void) length;
  (void) userParam;

  // ignore non-significant error/warning codes
  if(id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

  std::cout << "---------------" << std::endl;
  std::cout << "Debug message (" << id << "): " <<  message << std::endl;

  switch (source)
  {
    case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
    case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
    case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
    case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
    case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
  }
  std::cout << std::endl;

  switch (type)
  {
    case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break;
    case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
    case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
    case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
    case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
    case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
    case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
  }
  std::cout << std::endl;

  switch (severity)
  {
    case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
    case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
    case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
    case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
  } std::cout << std::endl;
  std::cout << std::endl;
}

#endif

Window::Window(std::string title, bool fullscreen)
  :
    _is_closed(false)
{
  if (!glfwInit()) {
    // could not init glfw!
    std::cerr << "error initialising GLFW" << std::endl;
    exit(1);
  }
  else {
    std::cout << "GLFW " << glfwGetVersionString() << " initialised" << std::endl;
  }

#ifdef MACOS
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

#ifdef DEBUG
  glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
#endif

  if (fullscreen) {
    GLFWmonitor *monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);

    glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

    this->w = mode->width;
    this->h = mode->height;

    glfw_window = glfwCreateWindow(mode->width, mode->height, title.c_str(), monitor, nullptr);
  }
  else {
    this->w = 1280;
    this->h = 720;
    glfw_window = glfwCreateWindow(this->w, this->h, title.c_str(), nullptr, nullptr);
  }

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
  std::cerr << "window singleton @ " << singleton_ptr << std::endl;

#ifdef DEBUG
  int flags;
  glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
  if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
    std::cout << "OpenGL debug messaging enabled" <<std::endl;
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(glDebugOutput, nullptr);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
  }
  else {
    std::cout << "WARNING! unable to start OpenGL debug messaging: OpenGL version may be too old." <<std::endl;
  }
#endif

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

unsigned int Window::get_w() const
{
  return this->w;
}

unsigned int Window::get_h() const
{
  return this->h;
}
