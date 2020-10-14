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

  game->play();
}
