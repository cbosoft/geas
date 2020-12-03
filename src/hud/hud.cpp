#include "hud.hpp"

#include "../text/textbox/textbox.hpp"

HUD::HUD(Transform *parent)
    :   Transform(parent)
{
    this->set_static_positioning();
    this->relative_position(Vec3({0, 0, 0.0}));
    this->_text = new Text(this, "assets/fonts/big_serif.png");
    this->_text->set_text("yo");
}

Renderable *HUD::renderable() const
{
    this->update();
    return Transform::renderable();
}