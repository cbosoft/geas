#include "quit_button.hpp"
#include "../../../../game/game.hpp"

void QuitButton::action()
{
    Game::singleton()->quit();
}