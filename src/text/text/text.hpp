#pragma once

#include <vector>

#include "../glyph/glyph.hpp"
#include "../../transform/transform.hpp"

class Text : public Transform, public Font {
public:
    Text(Transform *parent, const std::string &font_name);

    void set_text(std::string s);

private:
    std::vector<Glyph *> _glyphs;
};