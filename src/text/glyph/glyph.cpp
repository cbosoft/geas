#include "glyph.hpp"

#include "../../renderable/renderable.hpp"

Glyph::Glyph(Transform *parent, const Font *font)
    :   Transform(parent)
    ,   _font(font)
    ,   _character(' ')
{
    this->_renderable = new Renderable(this);
    this->_renderable->set_texture(font->texture_name());
}

void Glyph::set_char(char c)
{
    this->_character = c;
    this->_renderable->current_frame(this->_font->get_index_of(c));
}

Renderable *Glyph::renderable() const
{
    return this->_renderable;
}