#include <iostream>
#include <chrono>

#include "game/game.hpp"
#include "geas_object/player/player.hpp"
#include "geas_object/tile/tile.hpp"

void player_add(Game *game, Scene *scene, int delay)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    std::cerr << "dropping player" << std::endl;
    auto *player = new Player(scene->root);
    game->set_player(player);
    player->absolute_position(Vec3({0, 100, 0.0}));
}

int main()
{
    Game *game = Game::singleton();
    auto *scene = new Scene();
    game->active_scene(scene);

    Physics::update_rate_hz(500);
    Physics::time_scale(1.0f);
    Physics::global_gravity_scale(1e-2);

    for (float x = -100.0f; x < 100.0f; x += 17.0f) {
        for (float y = -250.0f; y < -200.0f; y += 17.0f) {
            auto *t = new Tile(scene->root, true, true);
            t->relative_position(Vec3({x, y, 0.0f}));
        }
    }

    std::thread(player_add, game, scene, 5000).detach();

    game->play();

}
