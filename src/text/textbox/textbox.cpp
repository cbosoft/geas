#include "../../geas_object/sliced_sprite/sliced_sprite.hpp"
#include "../text/text.hpp"
#include "textbox.hpp"

TextBox::TextBox(Transform *parent, const std::string &font_name, const Vec2 &size, const std::string &fill_sprite)
    :   Text(parent, font_name)
{
    [[maybe_unused]] auto *ss = new SlicedSprite(this, size, fill_sprite);
    this->relative_position(Vec3({4.0f, size.y()-4.0f-this->height(), 0.0f}));
}