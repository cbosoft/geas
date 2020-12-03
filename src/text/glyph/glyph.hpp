#pragma once

#include "../../transform/transform.hpp"
#include "../font/font.hpp"

class Font;

class Glyph : public Transform {
public:
    Glyph(Transform *parent, const Font *font);

    Renderable *renderable() const override;

    void set_char(char c);

private:
    const Font *_font;
    char _character;
    Renderable *_renderable;
};