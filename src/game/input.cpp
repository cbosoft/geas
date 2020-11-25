#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "game.hpp"
#include "../scene/ui/ui.hpp"

void Game::process_input(int key, int scancode, int action, int mods)
{
    if (this->active_scene()->is_ui()) {
        this->process_input_ui(key, scancode, action, mods);
    }
    else {
        this->process_input_game(key, scancode, action, mods);
    }
}


void Game::process_input_game(int key, int scancode, int action, int mods)
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

        case GLFW_KEY_DOWN:
        case GLFW_KEY_LEFT_SHIFT:
            if (this->player) {
                if (action == GLFW_PRESS) {
                    this->player->crouch(true);
                }
                else if (action == GLFW_RELEASE) {
                    this->player->crouch(false);
                }
            }

        default:
            break;

    }
}

void Game::process_input_ui(int key, int scancode, int action, int mods)
{
  (void) scancode;
  (void) action;
  (void) mods;

  auto *ui = (UI *)this->active_scene();

  switch (key) {

      case GLFW_KEY_ESCAPE:
      case GLFW_KEY_Q:
          ui->cancel();
          break;

      case GLFW_KEY_D:
      case GLFW_KEY_RIGHT:
          if (this->player && action == GLFW_PRESS) {
              ui->move(UIDir_Right);
          }
          break;

      case GLFW_KEY_A:
      case GLFW_KEY_LEFT:
          if (action == GLFW_PRESS) {
              ui->move(UIDir_Left);
          }
          break;

      case GLFW_KEY_W:
      case GLFW_KEY_UP:
          if (action == GLFW_PRESS) {
              ui->move(UIDir_Up);
          }
          break;

      case GLFW_KEY_S:
      case GLFW_KEY_DOWN:
          if (action == GLFW_PRESS) {
              ui->move(UIDir_Down);
          }
          break;

      case GLFW_KEY_ENTER:
      case GLFW_KEY_E:
      case GLFW_KEY_K:
      case GLFW_KEY_SPACE:
          ui->accept();
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
