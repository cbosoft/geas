#include "main_menu.hpp"

#include "../../geas_object/tile/animated_tile/animated_tile.hpp"

MainMenu::MainMenu()
    :   UI("main_menu")
{
    auto *background = new AnimatedTile(this, Vec2({640.0f, 480.0f}), "assets/ui/backgrounds/main_menu.png");
    background->relative_position(Vec3({-320,-240,0}));
    auto *continue_button = new SceneTransitButton(this, Vec2({24.0f, -24.0f}), "continue", "assets/fonts/vict.png", "continue", "test_room");
    auto *quit_button = new QuitButton(this, Vec2({24.0f, -56.0f}), "quit", "assets/fonts/vict.png", "quit");

    continue_button->set_direction(UIDir_Down, quit_button);
    quit_button->set_direction(UIDir_Up, continue_button);

    // TODO: make a selector class
    auto *selector = new GeasObject(this);
    this->set_selection_hint(selector);
    auto *r = new Renderable(selector);
    r->set_texture("assets/textures/selector.png");
    r->size(Vec2({96,32}));
    selector->renderable(r);
    this->set_selection_offset(Vec2({-8.0, -8.0}));

    this->select(continue_button);
}