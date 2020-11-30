#include <iostream>
#include <chrono>

#include "game/game.hpp"
#include "geas_object/tile/tile.hpp"
#include "geas_object/actor/player/player_animator/player_animator.hpp"
#include "resourcemanager/resourcemanager.hpp"
#include "geas_object/actor/player/player.hpp"
#include "util/font/font.hpp"
#include "util/textbox/textbox.hpp"
#include "scene/ui/main_menu/main_menu.hpp"
#include "scene/room/room.hpp"

void player_add(Game *game, Scene *scene, int delay)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    std::cerr << "dropping player" << std::endl;
    auto *player = new Player(scene->layers["main"]);
    game->set_player(player);
    scene->camera()->target(player);
    player->absolute_position(Vec3({0, 100, 0.0}));
    player->enable();
}

int main()
{
    Game *game = Game::singleton();
    auto *test_room = Room::from_file("assets/rooms/test.json");
    auto *main_menu = new MainMenu();
    game->active_scene(main_menu);
    game->add_scene(test_room);

    Physics::update_rate_hz(500);
    Physics::time_scale(1.0f);
    Physics::global_gravity_scale(1e-2);

    // auto *t = new Tile(scene->layers["main"], 64.0f, "assets/textures/industrialist1.png");
    // t->absolute_position(Vec3({64.0f, -136.0f, 0.0f}));
    // auto *p = new PlayerAnimator(*t);
    // p->load_animations("assets/textures/industrialist1.png");
    // p->set_state(0, 0, true, false);
    // p->speed(0.1f);

    // auto f = new Font("assets/textures/vict.png");
    // f->scale(0.5f);
    // auto tb = new TextBox(scene->layers["main"], Vec2({150.0f, 16.0f}), "assets/textures/text_background.png", "begone foul child!", *f);
    // (void)tb;

    //std::thread(player_add, game, scene, 500).detach();

    game->play();

}
