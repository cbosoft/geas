#include "pause_menu.hpp"
#include "../../game/game.hpp"


void PauseMenu::activate()
{
    auto *game = Game::singleton();
    auto *prev = game->previously_active_scene();
    this->return_to_game->set_destination(prev->name());

    UI::activate();
}