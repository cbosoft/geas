#include "scene_transition_element.hpp"
#include "../../../../game/game.hpp"

void SceneTransitButton::action()
{
    auto *game = Game::singleton();
    game->set_tunnel_tag(game->active_scene()->name(), _destination, "");
    game->transition_to(this->_destination, 500);
}