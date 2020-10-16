#include <thread>
#include <iostream>

#include "../globject/globject.hpp"
#include "game.hpp"

Game::Game()
  :
    win("GEAS", false),
    time(0.0), time_delta(0.0), time_scale(1.0),
    time_irl(0.0), time_delta_irl(0.0)
{
  this->win.register_input_callback(Game::input_callback_wrapper);
}

Game::~Game()
{
  // do nothing
}

void Game::play()
{
  this->_is_alive = true;

  // // start physics thread(s)
  // // TODO

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

  
  auto t0 = std::chrono::high_resolution_clock::now();
  while (this->is_alive()) {
    win.prepaint();

    // TODO move to physics thread
    auto t1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> fs = t1 - t0;
    t0 = t1;
    this->time_delta_irl = fs.count();
    this->time_irl += this->time_delta_irl;

    this->time_delta = this->time_delta_irl * this->time_scale;
    this->time += this->time_delta;
    Physics::update();

    std::list<GeasObject *> surviving;
    for ( auto obj : this->objects ) {
      obj->draw();
      if (obj->is_marked_for_destruction()) {
        delete obj;
      }
      else {
        surviving.push_back(obj);
      }
    }
    this->objects = surviving;

    win.postpaint();

    if (win.is_closed()) {
      this->is_alive(false);
    }
  }
}

void Game::push_object(GeasObject *object)
{
  this->objects.push_back(object);
}

bool Game::is_alive() const
{
  // TODO: mutex and lock guard
  return this->_is_alive;
}

void Game::is_alive(bool v)
{
  // TODO: mutex and lock guard
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
