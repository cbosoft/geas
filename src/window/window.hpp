#pragma once

#include <string>
#include <list>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../vector/vector.hpp"

class GLObject;

// OpenGL/GLFW window interface
class Window {

  public:
    friend class GLObject;
    static Window &singleton(int w, int h, std::string title);
    static Window &singleton();

    ~Window();

    void run();
    void push_object(GLObject *objects);
    void process_input(int key, int scancode, int action, int mods);
    Vec2 world_to_win(Vec2);
    Vec3 world_to_win(Vec3);

  private:

    void process_events();
    Window(int w, int h, std::string title);

    unsigned int w, h;

    GLFWwindow* glfw_window;
    std::list<GLObject *> objects;
    Vec2 camera_position, camera_aperture_size;
};
