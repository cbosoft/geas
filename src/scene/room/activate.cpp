#include <iostream>
#include "../../game/game.hpp"
#include "room.hpp"

void Room::activate()
{
    auto *game = Game::singleton();

    Player *p = game->get_player();
    if (!p) {
        p = new Player(this);
        game->set_player(p);
    }
    else {
        p->parent(this);
    }

    // if tag unset or not in tunnel positions, don't reposition player!
    auto it = this->tunnel_positions.find(game->get_tunnel_tag());
    if (it != this->tunnel_positions.end()) {
        Vec3 pos3 = it->second.promote(0.0f);
        p->absolute_position(pos3);
    }
    this->camera()->target(p);
    this->camera()->absolute_position(p->absolute_position());
    Scene::activate();
}