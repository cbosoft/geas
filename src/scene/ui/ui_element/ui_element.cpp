#include <iostream>

#include "ui_element.hpp"
#include "../../../geas_object/tile/tile.hpp"
#include "../../../text/text/text.hpp"

UIElement::UIElement(Transform *parent, const Vec2 &position, const std::string &iname, const std::string &font_name, const std::string &text)
    :   Transform(parent)
    ,   name(iname)
{
    this->relative_position(position.promote(0.0f));
    auto *t = new Text(this, font_name);
    t->set_text(text);
}

UIElement *UIElement::move(UIDirection dir)
{
    auto it = this->targets.find(dir);
    if (it != this->targets.end()) {
        return it->second;
    }
    return this;
}

const std::string &UIElement::get_name() const
{
    return this->name;
}

void UIElement::set_direction(UIDirection dir, UIElement *dest)
{
    this->targets[dir] = dest;
}