#include <iostream>

#include "game/game.hpp"
#include "player/player.hpp"

int main()
{
    Game *game = Game::singleton();

    {
        auto *player = new Player();
        player->absolute_position(Vec3({0, 20, 0.0}));
        game->push_object(player);
    }

    {
        auto *player = new Player();
        player->sprite->request_animation("idle");
        player->absolute_position(Vec3({0, 0, 0.0}));
        player->physics->set_gravity(0.0);
        player->physics->set_fixed();
        game->push_object(player);
    }

    game->play();
}
