#pragma once

#include "../ui_element.hpp"

class SceneTransitButton : public UIElement {
public:
    SceneTransitButton(Transform *parent, const Vec2 &position, const std::string &name, const std::string &font, const std::string &text, const std::string &destination);

    void action() override;

    void set_destination(const std::string &destination);

private:
    std::string _destination;
};