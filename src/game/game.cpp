#include <thread>
#include <iostream>

#include "../globject/globject.hpp"
#include "game.hpp"

Game::Game()
  :   time(0.0)
    , time_delta(0.0)
    , time_scale(1.0)
    , time_irl(0.0)
    , time_delta_irl(0.0)
    , _active_scene(nullptr)
    , _is_alive(true)
{
    this->renderer = Renderer::get(this);
    // TODO: register input callback with renderer
    //this->win.register_input_callback(Game::input_callback_wrapper);
}

Game::~Game()
{
  // do nothing
  // TODO delete scenes
}

void Game::play()
{
    this->_is_alive = true;
    //this->threads.emplace_back(&Game::physics_thread_worker, this);
    this->threads.emplace_back(&Game::input_thread_worker, this);

    this->graphics_thread_worker();

    for (auto &thread: this->threads) {
        thread.join();
    }
}

//   auto t0 = std::chrono::high_resolution_clock::now();
//   while (!glfwWindowShouldClose(this->glfw_window)) {
//     auto t1 = std::chrono::high_resolution_clock::now();
//     std::chrono::duration<float> fs = t1 - t0;
//     t0 = t1;
//     float dt = fs.count();
//     (void) dt;

void Game::graphics_thread_worker()
{
  std::cerr << "start gfx thread " << std::endl;
  this->renderer->run();
}

// void Game::push_object(GeasObject *object)
// {
//   this->objects.push_back(object);
// }

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