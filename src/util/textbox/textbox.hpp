#pragma once

#include <string>

#include "../../transform/transform.hpp"
#include "../font/font.hpp"

class TextBox : public Transform {
public:
    TextBox(Transform *parent, const Vec2 &size, const std::string &fill_sprite, const std::string &text, const Font &font);
};