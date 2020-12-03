#pragma once

#include "../ui_element.hpp"

class QuitButton : public UIElement {
public:
    QuitButton(Transform *parent, const Vec2 &position, const std::string &name, const std::string &font, const std::string &text);

    void action() override;

};
