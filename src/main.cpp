#include <iostream>
#include <chrono>

#include "game/game.hpp"
#include "geas_object/tile/tile.hpp"
#include "geas_object/actor/player/player_animator/player_animator.hpp"
#include "resourcemanager/resourcemanager.hpp"
#include "geas_object/actor/player/player.hpp"
#include "util/font/font.hpp"

void player_add(Game *game, Scene *scene, int delay)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    std::cerr << "dropping player" << std::endl;
    auto *player = new Player(scene->layers["main"]);
    game->set_player(player);
    scene->camera()->target(player);
    player->absolute_position(Vec3({0, 100, 0.0}));
    player->enable();
}

int main()
{
    Game *game = Game::singleton();
    auto *scene = Scene::from_file("level1.json");
    game->active_scene(scene);
    scene->enable();

    Physics::update_rate_hz(500);
    Physics::time_scale(1.0f);
    Physics::global_gravity_scale(1e-2);

    auto *t = new Tile(scene->layers["main"], 64.0f, "textures/industrialist1.png");
    t->absolute_position(Vec3({0.0f, -32.0f, 0.0f}));
    auto *p = new PlayerAnimator(*t);
    p->load_animations("textures/industrialist1.png");
    p->set_state(0, true);
    p->speed(0.1f);

    auto f = new Font("textures/vict.png");
    f->scale(0.8f);
    auto transform = new Transform(scene->layers["main"]);
    transform->relative_position(Vec3({0.0f, 64.0f, 0.0f}));
    f->render_text(transform, "begone foul child!", Vec2(128.0f));

    std::thread(player_add, game, scene, 500).detach();

    game->play();

}
