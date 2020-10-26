#pragma once

#include <thread>
#include <list>
#include <vector>

#include "../geas_object/geas_object.hpp"
#include "../renderer/renderer.hpp"

class GLObject;
class Game {

  public:
    ~Game();
    static Game *singleton();

    void play();
    //void push_object(GeasObject *object);

    bool is_alive() const;
    void is_alive(bool v);

    float get_time_delta() const;
    float get_time() const;

    [[nodiscard]] Scene *active_scene() const;
    void active_scene(Scene *scene);
    void active_scene(unsigned int i);
    void process_input(int key, int scancode, int action, int mods);

  private:
    Game();

    //static void input_callback_wrapper(GLFWwindow *win, int key, int scancode, int action, int mods);

    void graphics_thread_worker();
    void physics_thread_worker();


    Renderer *renderer;
    float time, time_delta, time_scale;
    float time_irl, time_delta_irl;
    std::list<std::thread> threads;
    //std::list<GeasObject *> objects; // unnecessary: objects are stored in scenes via transforms.
    std::vector<Scene *> scenes;
    Scene *_active_scene;
    bool _is_alive;

};
