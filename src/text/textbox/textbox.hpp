#pragma once

#include <string>

#include "../../transform/transform.hpp"
#include "../text/text.hpp"

class TextBox : public Text {
public:
    TextBox(Transform *parent, const std::string &font_name, const Vec2 &size, const std::string &fill_sprite);
};