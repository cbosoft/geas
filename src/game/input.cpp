#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "game.hpp"

void Game::process_input(int key, int scancode, int action, int mods)
{
  (void) scancode;
  (void) action;
  (void) mods;

  switch (key) {

    case GLFW_KEY_ESCAPE:
        // TODO: quit
        this->is_alive(false);
        break;

    default:
      break;

  }
}
