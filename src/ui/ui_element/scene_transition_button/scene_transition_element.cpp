#include "scene_transition_element.hpp"

SceneTransitButton::SceneTransitButton(Transform *parent, const Vec2 &position, const std::string &name, const std::string &font, const std::string &text, const std::string &destination)
    : UIElement(parent, position, name, font, text)
    , _destination(destination)
{
    // do nothing
}

void SceneTransitButton::set_destination(const std::string &destination)
{
    this->_destination = destination;
}