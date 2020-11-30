#include <iostream>
#include "ui.hpp"

UI::UI(const std::string &name)
    : Scene(name)
    , selected(nullptr)
    , selection_hint(nullptr)
{

}

void UI::accept()
{
    if (this->selected)
        this->selected->action();
}

void UI::cancel()
{
    // do nothing
}

void UI::move(UIDirection dir)
{
    if (this->selected) {
        this->select(this->selected->move(dir));
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