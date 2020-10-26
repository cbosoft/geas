#include <iostream>
#include <chrono>

#include "game/game.hpp"
#include "player/player.hpp"

// void player_add(Game *game, Player *player, int delay)
// {
//     std::this_thread::sleep_for(std::chrono::milliseconds(delay));
//     std::cerr << "adding player" << std::endl;
//     game->push_object(player);
// }

int main()
{
    Game *game = Game::singleton();
    // Transform t;

    // {
    //     auto *player = new Player(&t);
    //     player->sprite->request_animation("idle");
    //     player->absolute_position(Vec3({0, 0, 0.0}));
    //     player->physics->set_gravity(0.0);
    //     player->physics->set_fixed();
    //     game->push_object(player);
    // }

    // {
    //     auto *player = new Player(&t);
    //     player->absolute_position(Vec3({0, 100, 0.0}));
    //     std::thread(player_add,game, player, 500).detach();
    // }

    Scene *scene = new Scene();

    game->active_scene(scene);
    game->play();

    //std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}
