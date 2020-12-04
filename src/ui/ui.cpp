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
    target_position += this->selector_offset;
    this->selection_hint->relative_position(target_position);
    this->selected = elem;
}

void UI::set_selection_offset(const Vec2 &offset)
{
    this->selector_offset = offset.promote(0.0f);
}

void UI::set_selection_hint(Transform *hint)
{
    delete this->selection_hint;
    this->selection_hint = hint;
}