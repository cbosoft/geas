#include "hud.hpp"

#include "../text/text/text.hpp"

HUD::HUD(Transform *parent)
    :   Transform(parent)
{
    this->set_static_positioning();
    this->relative_position(Vec3({-320, -240, 0.0}));
    this->_text = new Text(this, "assets/fonts/big_serif.png");
    this->_text->relative_position(Vec3({20, 440}));
    this->t0 = std::chrono::system_clock::now();
}

Renderable *HUD::renderable() const
{
    this->update();
    return Transform::renderable();
}