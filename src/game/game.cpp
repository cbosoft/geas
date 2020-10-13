#include <thread>
#include <iostream>

#include "../globject/globject.hpp"
#include "game.hpp"

Game::Game()
  :
    win(1280, 720, "GEAS")
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

void Game::graphics_thread_worker()
{
  std::cerr << "start gfx thread " << std::endl;
  while (this->is_alive()) {
    win.prepaint();

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
