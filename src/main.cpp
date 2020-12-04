#include <iostream>
#include <chrono>

#include "game/game.hpp"
#include "geas_object/tile/tile.hpp"
#include "resourcemanager/resourcemanager.hpp"
#include "geas_object/actor/player/player.hpp"
#include "ui/main_menu/main_menu.hpp"
#include "ui/pause_menu/pause_menu.hpp"
#include "scene/room/room.hpp"

int main()
{
    Game *game = Game::singleton();
#ifdef DEBUG
    //game->show_colliders(true);
#endif
    auto *test_room = Room::from_file("assets/rooms/test.json");
    auto *another = Room::from_file("assets/rooms/test2.json");
    auto *main_menu = new MainMenu();
    auto *pause_menu = new PauseMenu();
    game->active_scene(main_menu);
    game->add_scene(test_room);
    game->add_scene(another);
    game->add_scene(pause_menu);

    Physics::update_rate_hz(500);
    Physics::time_scale(1.0f);
    Physics::global_gravity_scale(1e-2);

    game->play();

}
