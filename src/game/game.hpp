#pragma once

#include <thread>
#include <list>

#include "../window/window.hpp"

class GLObject;
class Game {

  public:
    ~Game();
    static Game *singleton();

    void play();
    void push_object(GLObject *object);

    bool is_alive() const;
    void is_alive(bool v);

  private:
    Game();

    static void input_callback_wrapper(GLFWwindow *win, int key, int scancode, int action, int mods);

    void graphics_thread_worker();
    void physics_thread_worker();
    void process_input(int key, int scancode, int action, int mods);

    Window win;


    bool _is_alive;
    std::list<std::thread> threads;
    std::list<GLObject *> objects;

};
