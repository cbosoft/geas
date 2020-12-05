#include <iostream>
#include <chrono>

#include "game/game.hpp"
#include "geas_object/tile/tile.hpp"
#include "behaviour/patroller/patroller.hpp"
#include "geas_object/actor/enemy/enemy.hpp"
#include "resourcemanager/resourcemanager.hpp"
#include "geas_object/actor/player/player.hpp"
#include "ui/main_menu/main_menu.hpp"
#include "ui/pause_menu/pause_menu.hpp"
#include "scene/room/room.hpp"

class PatrollingEnemy : public Enemy {
public:

    PatrollingEnemy(Transform *parent)
        : Enemy(parent, 3.0f)
    {
        [[maybe_unused]] auto *b = new Patroller(this);
        auto *r = new Renderable(this);
        r->set_texture("assets/textures/boy.png");
        r->size(Vec2({32.0f, 32.0f}));
        this->physics->set_gravity(1.5e1f);
        this->renderable(r);
    }

};

int main()
{
    Game *game = Game::singleton();
#ifdef DEBUG
    game->show_colliders(true);
#endif
    auto *test_room = Room::from_file("assets/rooms/test.json");
    auto *another = Room::from_file("assets/rooms/test2.json");
    auto *main_menu = new MainMenu();
    auto *pause_menu = new PauseMenu();
    game->active_scene(main_menu);
    game->add_scene(test_room);
    game->add_scene(another);
    game->add_scene(pause_menu);

    auto *p = new PatrollingEnemy(test_room->layers["main"]);
    p->absolute_position(Vec3({500.0f, 512.0f, 0.0f}));

    Physics::update_rate_hz(500);
    Physics::time_scale(1.0f);
    Physics::global_gravity_scale(1e-2f);

    game->play();

}
