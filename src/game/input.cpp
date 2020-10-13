#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "game.hpp"

void Game::input_callback_wrapper(GLFWwindow *window, int key, int scancode, int action, int mods)
{
  (void) window;
  Game::singleton()->process_input(key, scancode, action, mods);
}

void Game::process_input(int key, int scancode, int action, int mods)
{
  (void) scancode;
  (void) action;
  (void) mods;

  switch (key) {

    case GLFW_KEY_ESCAPE:
      this->win.quit();
      break;

    default:
      break;

  }
}
