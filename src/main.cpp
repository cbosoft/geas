#include "game/game.hpp"

int main()
{
    Game *game = Game::singleton();
    game->load_rooms();
    game->init_menus();
    game->active_scene("splash");

#ifdef DEBUG
    //game->show_colliders(true);
#endif

    game->play();
}
