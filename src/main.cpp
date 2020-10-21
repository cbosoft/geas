#include <iostream>
#include <chrono>

#include "game/game.hpp"
#include "player/player.hpp"

void player_add(Game *game, Player *player, int delay)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    std::cerr << "adding player" << std::endl;
    game->push_object(player);
}

int main()
{
    Game *game = Game::singleton();

    {
        auto *player = new Player();
        player->sprite->request_animation("idle");
        player->absolute_position(Vec3({0, 0, 0.0}));
        player->physics->set_gravity(0.0);
        player->physics->set_fixed();
        game->push_object(player);
    }

    {
        auto *player = new Player();
        player->absolute_position(Vec3({0, 100, 0.0}));
        std::thread(player_add,game, player, 500).detach();
    }

    game->play();
}
