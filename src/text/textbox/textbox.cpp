#include "../../geas_object/sliced_sprite/sliced_sprite.hpp"
#include "textbox.hpp"

TextBox::TextBox(Transform *parent, const Vec2 &size, const std::string &fill_sprite, const std::string &text, const Font &font)
    : Transform(parent)
{
    (void) size;
    (void) fill_sprite;
    (void) text;
    (void) font;

    [[maybe_unused]] auto *ss = new SlicedSprite(this, size, fill_sprite);
    auto *tl = new Transform(this);
    tl->relative_position(Vec3({4.0f, size.y()-4.0f-font.height(), 0.0f}));
    font.render_text(tl, text, size);

}