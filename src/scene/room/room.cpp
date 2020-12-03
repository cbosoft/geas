#include "room.hpp"
#include "../../hud/hud.hpp"

Room::Room(const std::string &name)
    :   Scene(name)
{
    // do nothing
    [[maybe_unused]] auto *hud = new HUD(this->hud());
}