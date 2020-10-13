#include "game.hpp"


Game *Game::singleton()
{
  static Game game;
  return &game;
}
