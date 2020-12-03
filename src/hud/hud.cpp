#include "hud.hpp"

#include "../text/textbox/textbox.hpp"

HUD::HUD(Transform *parent)
    :   Transform(parent)
{
    this->set_static_positioning();
    this->relative_position(Vec3({-240, 150, 0.0}));
    this->_text = new TextBox(this, "assets/fonts/vict.png", Vec2({128, 16}), "assets/textures/text_background.png");
    this->_text->set_text("hp:                            ");
    this->t0 = std::chrono::system_clock::now();
}

Renderable *HUD::renderable() const
{
    this->update();
    return Transform::renderable();
}