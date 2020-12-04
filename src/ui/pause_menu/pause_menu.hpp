#pragma once

#include "../ui.hpp"
#include "../ui_element/elements.hpp"

class PauseMenu : public UI {
public:
    PauseMenu();

    void activate() override;

private:
    SceneTransitButton *return_to_game;
};