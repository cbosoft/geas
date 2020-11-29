#include <iostream>
#include "ui.hpp"

UI::UI()
    : Scene()
    , selected(nullptr)
    , selection_hint(nullptr)
{

}

void UI::accept()
{
    // TODO: accept on currently selected accept action
}

void UI::cancel()
{
    // TODO: cancel on currently selected UIElement
}

void UI::move(UIDirection dir)
{
    if (this->selected) {
        std::string name = this->selected->move(dir);
        UIElement *target = this->elements[name];
        this->select(target);
    }
}

void UI::select(UIElement *elem)
{
    if (elem == this->selected)
        return;

    if (!this->selection_hint)
        return;

    Vec3 target_position = elem->relative_position();
    target_position += Vec3({-24.0f, 0.0f, 0.0f});
    this->selection_hint->relative_position(target_position);
    this->selected = elem;
}