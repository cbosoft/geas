#include "main_menu.hpp"

#include "../../../geas_object/tile/tile.hpp"

MainMenu::MainMenu()
    :   UI("main_menu")
{
    Font font{"assets/fonts/vict.png"};
    [[maybe_unused]] auto *background = new Tile(this, 640.0f, "assets/textures/plain_ui_bg.png");
    auto *continue_button = new SceneTransitButton(this, Vec2(0.0f), "continue", "continue", font, "test_room");
    auto *quit_button = new QuitButton(this, Vec2({0.0f, -32.0f}), "quit", "quit", font);

    continue_button->set_direction(UIDir_Down, quit_button);
    quit_button->set_direction(UIDir_Up, continue_button);



    this->selection_hint = new Tile(this, 16.0f, "assets/textures/arrow.png");
    this->select(continue_button);
}