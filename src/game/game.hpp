#pragma once

#include <thread>
#include <list>
#include <map>
#include <mutex>

#include "../geas_object/actor/player/player.hpp"
#include "../renderer/renderer.hpp"
#include "../util/tsq.hpp"
#include "../event/event.hpp"
#include "input.hpp"

class Game {

  public:
    ~Game();
    static Game *singleton();

    void load_rooms();
    void init_menus();

    void play();
    void push_input(PlayerInput *input);

    bool is_alive() const;
    void is_alive(bool v);
    void quit();

    float get_time_delta() const;
    float get_time() const;

    [[nodiscard]] Scene *active_scene() const;
    void active_scene(Scene *scene, bool fade_in=false);
    void active_scene(const std::string& scene_name, bool fade_in=false);
    [[nodiscard]] Scene *previously_active_scene() const;
    void add_scene(Scene *scene);
    void transition_to(Scene *scene, unsigned int delay_ms=100);
    void transition_to(const std::string &scene_name, unsigned int delay_ms=800);

    void process_input(int key, int scancode, int action, int mods);

    void set_player(Player *obj);
    [[nodiscard]] Player *get_player() const;

    void set_tunnel_tag(const std::string &tag);
    void set_tunnel_tag(const std::string &scene_A, const std::string &scene_B, const std::string &descriptor);
    std::string get_tunnel_tag();

    static std::string gen_tunnel_tag(const std::string &A, const std::string &B, const std::string &descriptor);

    bool recently_transitioned();

    void push_event(Event *event);

#ifdef DEBUG
    void show_colliders(bool v);
    [[nodiscard]] bool should_show_colliders() const;
#endif

  private:
    Game();

    void process_input_game(int key, int scancode, int action, int mods);
    void process_input_ui(int key, int scancode, int action, int mods);

    void animator_thread_worker();
    void graphics_thread_worker();
    void physics_thread_worker();
    void input_thread_worker();
    void behaviour_thread_worker();
    void audio_thread_worker();
    void events_thread_worker();

    void set_recently_transitioned();

    Renderer *renderer;
    float time, time_delta, time_scale;
    float time_irl, time_delta_irl;
    std::list<std::thread> threads;
    std::map<std::string, Scene *> scenes;
    Scene *_active_scene, *_previous_scene;
    bool _is_alive;
    ThreadedQueue<PlayerInput *> input_queue;
    std::list<Event *> events_queue;
    typedef std::lock_guard<std::mutex> lock_guard;
    mutable std::mutex mutex;
    Player *player;
    std::string tunnel_tag;
    bool _recently_transitioned;

#ifdef DEBUG
    bool _show_colliders;
#endif

};
