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
          this->is_alive(false);
          break;

      case GLFW_KEY_D:
      case GLFW_KEY_RIGHT:
          if (this->player) {
              switch (action) {
                  case GLFW_RELEASE:
                      this->player->move(-1);
                      break;
                  case GLFW_PRESS:
                      this->player->move(1);
                      break;

                  default:
                  case GLFW_REPEAT:
                      break;
              }
          }
          break;

      case GLFW_KEY_A:
      case GLFW_KEY_LEFT:
          if (this->player) {
              switch (action) {
                  case GLFW_RELEASE:
                      this->player->move(1);
                      break;
                  case GLFW_PRESS:
                      this->player->move(-1);
                      break;

                  default:
                  case GLFW_REPEAT:
                      break;
              }
          }
          break;

      case GLFW_KEY_W:
      case GLFW_KEY_UP:
      case GLFW_KEY_SPACE:
          if (this->player && action == GLFW_PRESS)
              this->player->jump();
          break;

      default:
          break;

  }
}

void Game::input_thread_worker()
{
    while(this->is_alive()) {
        PlayerInput *input = this->input_queue.pop();

        if (input) {
            this->process_input(input->keycode, input->scancode, input->action, input->mods);
            delete input;
        }

        //std::this_thread::sleep_for(std::chrono::microseconds(100));

    }
}
