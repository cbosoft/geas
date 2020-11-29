#pragma once

#include "../ui_element.hpp"

class SceneTransitButton : public UIElement {
public:
    SceneTransitButton(Transform *parent, const Vec2 &position, const std::string &name, const std::string &text, const Font &font, const std::string &destination);

    void action() override;

private:
    std::string _destination;
};