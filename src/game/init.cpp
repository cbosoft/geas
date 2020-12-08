#include "game.hpp"

#include "../resourcemanager/resourcemanager.hpp"
#include "../scene/room/room.hpp"
#include "../ui/main_menu/main_menu.hpp"
#include "../ui/pause_menu/pause_menu.hpp"

void Game::load_rooms()
{
    std::vector<json> room_jsons = ResourceManager::singleton().get_matching_metadata("assets/rooms/%");
    for (const auto &room_json : room_jsons) {
        auto *room = Room::from_json(room_json);
        this->add_scene(room);
    }
}

void Game::init_menus()
{
    this->add_scene(new MainMenu());
    this->add_scene(new PauseMenu());
}
