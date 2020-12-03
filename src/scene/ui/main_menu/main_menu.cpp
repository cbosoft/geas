#include "main_menu.hpp"

#include "../../../geas_object/tile/animated_tile/animated_tile.hpp"

MainMenu::MainMenu()
    :   UI("main_menu")
{
    auto *background = new AnimatedTile(this, 640.0f, "assets/textures/plain_ui_bg.png");
    background->relative_position(Vec3({-320,-320,0}));
    auto *continue_button = new SceneTransitButton(this, Vec2(0.0f), "continue", "assets/fonts/big_serif.png", "continue", "test_room");
    auto *quit_button = new QuitButton(this, Vec2({0.0f, -32.0f}), "quit", "assets/fonts/big_serif.png", "quit");

    continue_button->set_direction(UIDir_Down, quit_button);
    quit_button->set_direction(UIDir_Up, continue_button);

    this->selection_hint = new Tile(this, 16.0f, "assets/textures/arrow.png");
    this->select(continue_button);
}