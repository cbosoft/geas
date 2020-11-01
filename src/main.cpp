#include <iostream>
#include <chrono>

#include "game/game.hpp"
#include "geas_object/player/player.hpp"

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

    {
        auto *player = new Player(scene->root);
        //player->sprite->request_animation("idle");
        player->absolute_position(Vec3({0, -100, 0.0}));
        player->physics->set_gravity(0.0);
        player->physics->set_fixed();
    }

    {
        std::thread(player_add, game, scene, 500).detach();
    }

    game->play();

}
