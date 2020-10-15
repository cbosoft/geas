#include <iostream>
#include <ctime>

#include "game/game.hpp"
#include "globject/quad.hpp"
#include "resourcemanager/resourcemanager.hpp"
#include "player/player.hpp"

int main(void)
{
  Game *game = Game::singleton();

  game->push_object(new Player());

  Player *player = new Player();
  player->position->set(Vec2({-600, -360}));
  player->physics->set_gravity(0.0);
  game->push_object(player);

  game->play();
}
