#pragma once

#include <string>
#include <list>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class GLObject;

// OpenGL/GLFW window interface
class Window {

  public:
    friend Window& window(int w, int h, std::string title);
    friend class GLObject;

    ~Window();

    void run();
    void process_events();
    void push_object(GLObject *objects);

  private:
    Window(int w, int h, std::string title);

    GLFWwindow* glfw_window;
    std::list<GLObject *> objects;
};

Window &window(int w, int h, std::string title);
