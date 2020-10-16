#include <iostream>

#include "game/game.hpp"
#include "player/player.hpp"

int main()
{
    Game *game = Game::singleton();

    {
        auto *player = new Player();
        player->transform->absolute_position(Vec3({-300, 360, 0.0}));
        game->push_object(player);
    }

    {
        auto *player = new Player();
        player->transform->absolute_position(Vec3({-300, -360, 0.0}));
        player->physics->set_gravity(0.0);
        game->push_object(player);
    }

    game->play();
}
