#include <iostream>
#include "../../game/game.hpp"
#include "room.hpp"

void Room::activate()
{
    auto *game = Game::singleton();
    Vec2 pos = this->tunnel_positions[game->get_tunnel_tag()];

    Player *p = game->get_player();
    if (!p) {
        p = new Player(this);
        game->set_player(p);
    }
    else {
        p->parent(this);
    }

    p->absolute_position(pos.promote(0.0f));
    this->camera()->target(p);
    Scene::activate();
}