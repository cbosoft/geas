#include <iostream>
#include <chrono>

#include "game/game.hpp"
#include "resourcemanager/resourcemanager.hpp"
#include "geas_object/player/player.hpp"

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
    auto *scene = Scene::from_file("level1.json");
    game->active_scene(scene);
    scene->enable();

    Physics::update_rate_hz(500);
    Physics::time_scale(1.0f);
    Physics::global_gravity_scale(1e-2);

    std::thread(player_add, game, scene, 500).detach();

    game->play();

}
