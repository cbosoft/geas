#pragma once

#include <string>
#include <map>

#include "../scene.hpp"
#include "../../geas_object/tile/tile.hpp"
#include "ui_direction.hpp"
#include "ui_element/ui_element.hpp"

class UI : public Scene {
public:


    void move(UIDirection dir);
    void accept();
    void cancel();

    bool is_ui() override { return true; }

private:
    UI();

    void select(UIElement *elem);

    std::map<std::string, UIElement *> elements;
    UIElement *selected;
    Tile *selection_hint;
};