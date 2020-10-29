#include <iostream>
#include <chrono>

#include "game/game.hpp"
#include "player/player.hpp"

void player_add(Scene *scene, int delay)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    std::cerr << "dropping player" << std::endl;
    auto *player = new Player(scene->root);
    player->absolute_position(Vec3({0, 1, 0.0}));
}

int main()
{
    Game *game = Game::singleton();
    auto *scene = new Scene();
    game->active_scene(scene);

    {
        auto *player = new Player(scene->root);
        //player->sprite->request_animation("idle");
        player->absolute_position(Vec3({0, -0.5f, 0.0}));
        player->physics->set_gravity(0.0);
        player->physics->set_fixed();
    }

    {
        std::thread(player_add, scene, 500).detach();
    }

    game->play();

}
