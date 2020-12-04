#include "pause_menu.hpp"

#include "../../geas_object/tile/animated_tile/animated_tile.hpp"

PauseMenu::PauseMenu()
    :   UI("pause_menu")
{
    auto *background = new AnimatedTile(this, 640.0f, "assets/textures/plain_ui_bg.png");
    background->relative_position(Vec3({-320,-320,0}));
    this->return_to_game = new SceneTransitButton(this, Vec2(0.0f), "continue", "assets/fonts/vict.png", "continue", "test_room");
    auto *quit_button = new QuitButton(this, Vec2({0.0f, -32.0f}), "quit", "assets/fonts/vict.png", "quit");

    this->return_to_game->set_direction(UIDir_Down, quit_button);
    quit_button->set_direction(UIDir_Up, this->return_to_game);

    // TODO: make a selector class
    auto *selector = new GeasObject(this);
    this->set_selection_hint(selector);
    auto *r = new Renderable(selector);
    r->set_texture("assets/textures/selector.png");
    r->size(Vec2({96,32}));
    selector->renderable(r);
    this->set_selection_offset(Vec2({-8.0, -8.0}));

    this->select(this->return_to_game);
}