#include "hud.hpp"
#include "../game/game.hpp"

void HUD::update() const
{
    auto *g = Game::singleton();
    auto *p = g->get_player();
    (void) p;

    // TODO update player hp display

}