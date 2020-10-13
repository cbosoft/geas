#pragma once

#include <string>
#include <list>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../vector/vector.hpp"

typedef void (*key_callback)(GLFWwindow* window, int key, int scancode, int action, int mods);

// OpenGL/GLFW window interface
class Window {

  public:
    friend class Game;
    static Window *singleton();

    ~Window();

    void run();
    void register_input_callback(key_callback func);
    void quit();
    bool is_closed();

    void prepaint();
    void postpaint();

    Vec2 world_to_win(Vec2);
    Vec3 world_to_win(Vec3);

  private:

    Window(int w, int h, std::string title);

    unsigned int w, h;
    bool _is_closed;

    GLFWwindow* glfw_window;
    Vec2 camera_position, camera_aperture_size;
};
