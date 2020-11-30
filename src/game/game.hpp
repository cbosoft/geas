#pragma once

#include <thread>
#include <list>
#include <map>
#include <mutex>

#include "../geas_object/actor/player/player.hpp"
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
    void quit();

    float get_time_delta() const;
    float get_time() const;

    [[nodiscard]] Scene *active_scene() const;
    void active_scene(Scene *scene);
    void active_scene(const std::string& scene_name);
    void add_scene(Scene *scene);
    void transition_to(Scene *scene, unsigned int delay_ms=800);
    void transition_to(const std::string &scene_name, unsigned int delay_ms=800);

    void process_input(int key, int scancode, int action, int mods);

    void set_player(Player *obj);
    [[nodiscard]] Player *get_player() const;

    void set_tunnel_tag(const std::string &tag);
    void set_tunnel_tag(const std::string &scene_A, const std::string &scene_B, const std::string &descriptor);
    std::string get_tunnel_tag();

  private:
    Game();

    void process_input_game(int key, int scancode, int action, int mods);
    void process_input_ui(int key, int scancode, int action, int mods);

    void animator_thread_worker();
    void graphics_thread_worker();
    void physics_thread_worker();
    void input_thread_worker();

    Renderer *renderer;
    float time, time_delta, time_scale;
    float time_irl, time_delta_irl;
    std::list<std::thread> threads;
    std::map<std::string, Scene *> scenes;
    Scene *_active_scene;
    bool _is_alive;
    ThreadedQueue<PlayerInput *> input_queue;
    typedef std::lock_guard<std::mutex> lock_guard;
    mutable std::mutex mutex;
    Player *player;
    std::string tunnel_tag;


};
