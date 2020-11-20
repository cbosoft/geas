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
    , _is_alive(true)
    , player(nullptr)
    , _camera(nullptr)
{
    this->renderer = Renderer::get(this);
}

Game::~Game()
{

    for (Scene *sceneptr : this->scenes) {
        delete sceneptr;
    }

}

void Game::play()
{
    this->_is_alive = true;
    this->threads.emplace_back(&Game::physics_thread_worker, this);
    this->threads.emplace_back(&Game::input_thread_worker, this);

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


Transform *Game::camera()
{
    if (this->_camera == nullptr)
        this->_camera = new Transform(this->_active_scene);
    return this->_camera;
}

void Game::camera(Transform *cam)
{
    this->_camera = cam;
}