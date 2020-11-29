#pragma once

#include <string>
#include <map>

#include "../scene.hpp"
#include "../../geas_object/tile/tile.hpp"
#include "ui_direction.hpp"
#include "ui_element/ui_element.hpp"

class UI : public Scene {
public:
    UI();

    virtual void move(UIDirection dir);
    virtual void accept();
    virtual void cancel();

    bool is_ui() override { return true; }

    friend class MainMenu;

private:

    void select(UIElement *elem);

    UIElement *selected;
    Tile *selection_hint;
};