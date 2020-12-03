#include "hud.hpp"

#include "../text/textbox/textbox.hpp"

HUD::HUD(Transform *parent)
    :   Transform(parent)
    ,   font("assets/fonts/big_serif.png")
    ,   hptext(new Transform(this))
{
    this->set_static_positioning();
    this->relative_position(Vec3({0, 0, 0.0}));
    this->font.render_text(this->hptext, "thing");
}

Renderable *HUD::renderable() const
{
    this->update();
    return Transform::renderable();
}