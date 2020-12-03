#include "text.hpp"

Text::Text(Transform *parent, const std::string &font_name)
    :   Transform(parent)
    ,   Font(font_name)
{
    // do nothing
}

void Text::set_text(std::string s)
{
    this->render_text(this, this->_glyphs, s);
}