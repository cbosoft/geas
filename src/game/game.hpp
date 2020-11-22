#pragma once

#include <thread>
#include <list>
#include <vector>
#include <mutex>

#include "../geas_object/player/player.hpp"
#include "../renderer/renderer.hpp"
#include "../util/tsq.hpp"
#include "input.hpp"

class Game {

  public:
    ~Game();
    static Game *singleton();

    void play();
    void push_input(PlayerInput *input);

    bool is_alive() const;
    void is_alive(bool v);

    float get_time_delta() const;
    float get_time() const;

    [[nodiscard]] Scene *active_scene() const;
    void active_scene(Scene *scene);
    void active_scene(unsigned int i);
    void process_input(int key, int scancode, int action, int mods);

    void set_player(Player *obj);
    [[nodiscard]] Player *get_player() const;

    void camera(Transform *cam);
    [[nodiscard]] Transform *camera();

  private:
    Game();

    void animator_thread_worker();
    void graphics_thread_worker();
    void physics_thread_worker();
    void input_thread_worker();

    Renderer *renderer;
    float time, time_delta, time_scale;
    float time_irl, time_delta_irl;
    std::list<std::thread> threads;
    std::vector<Scene *> scenes;
    Scene *_active_scene;
    bool _is_alive;
    ThreadedQueue<PlayerInput *> input_queue;
    typedef std::lock_guard<std::mutex> lock_guard;
    mutable std::mutex mutex;
    Player *player;


};
