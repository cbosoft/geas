#pragma once

#include <string>
#include <map>

#include "../scene/scene.hpp"
#include "../geas_object/tile/tile.hpp"
#include "ui_direction.hpp"
#include "ui_element/ui_element.hpp"

class UI : public Scene {
public:
    UI(const std::string &name);

    virtual void move(UIDirection dir);
    virtual void accept();
    virtual void cancel();

    void select(UIElement *elem);
    void set_selection_offset(const Vec2 &offset);
    void set_selection_hint(Transform *hint);

    bool is_ui() override { return true; }

private:

    UIElement *selected;
    Transform *selection_hint;

    Vec3 selector_offset;
};