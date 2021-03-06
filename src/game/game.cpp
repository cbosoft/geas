#include <thread>
#include <iostream>

#include "game.hpp"

Game::Game()
  :   time(0.0)
    , time_delta(0.0)
    , time_scale(1.0)
    , time_irl(0.0)
    , time_delta_irl(0.0)
    , _active_scene(nullptr)
    , _previous_scene(nullptr)
    , _is_alive(true)
    , player(nullptr)
    , _recently_transitioned(false)
#ifdef DEBUG
    , _show_colliders(false)
#endif
{
    this->renderer = Renderer::get(this);
}

Game::~Game()
{

    for (const auto &kv : this->scenes) {
        Scene *sceneptr = kv.second;
        delete sceneptr;
    }

    for (const auto &event : this->events_queue) {
        delete event;
    }

}

void Game::play()
{
    this->_is_alive = true;
    this->threads.emplace_back(&Game::physics_thread_worker, this);
    this->threads.emplace_back(&Game::input_thread_worker, this);
    this->threads.emplace_back(&Game::animator_thread_worker, this);
    this->threads.emplace_back(&Game::behaviour_thread_worker, this);
    this->threads.emplace_back(&Game::audio_thread_worker, this);
    this->threads.emplace_back(&Game::events_thread_worker, this);

    this->graphics_thread_worker();

    for (auto &thread: this->threads) {
        thread.join();
    }
}

void Game::graphics_thread_worker()
{
  std::cerr << "start gfx thread " << std::endl;
  this->renderer->run();
}

bool Game::is_alive() const
{
    lock_guard(this->mutex);
    return this->_is_alive;
}

void Game::is_alive(bool v)
{
    lock_guard(this->mutex);
    this->_is_alive = v;
}

void Game::quit()
{
    this->is_alive(false);
}

float Game::get_time_delta() const
{
    return this->time_delta;
}

float Game::get_time() const
{
    return this->time;
}


void Game::push_input(PlayerInput *input)
{
    this->input_queue.push(input);
}


void Game::set_player(Player *obj)
{
    this->player = obj;
}


Player *Game::get_player() const
{
    return this->player;
}

bool Game::recently_transitioned()
{
    std::scoped_lock _lock(this->mutex);
    bool rv = this->_recently_transitioned;
    this->_recently_transitioned = false;
    return rv;
}

void Game::set_recently_transitioned()
{
    std::scoped_lock _lock(this->mutex);
    this->_recently_transitioned = true;

}

Scene *Game::previously_active_scene() const
{
    return this->_previous_scene;
}