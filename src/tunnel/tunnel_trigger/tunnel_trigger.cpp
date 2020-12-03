#include "tunnel_trigger.hpp"
#include "../../game/game.hpp"

TunnelTrigger::TunnelTrigger(GeasObject &owner, const Vec4 &rect, const std::string &destination, const std::string &descriptor)
    :   Trigger(owner, rect)
    ,   destination(destination)
    ,   descriptor(descriptor)
{
    // do nothing
}

void TunnelTrigger::on_trigger(GeasObject &with)
{
    auto *game = Game::singleton();
    GeasObject *p = game->get_player();
    if (p == &with) {
        // transport player to destination
        std::string current_scene = game->active_scene()->name();
        game->set_tunnel_tag(current_scene, this->destination, this->descriptor);
        game->transition_to(this->destination);
    }
}