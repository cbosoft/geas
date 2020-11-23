#include "../../resourcemanager/resourcemanager.hpp"
#include "../json.hpp"
#include "font.hpp"

Font::Font(const std::string &font_sheet)
    : texture_name(font_sheet)
    , height(16.0f)
    , _line_spacing(1.5)
{
    json j = ResourceManager::singleton().get_metadata(font_sheet);
    this->height = j["height"];
    int index = 0;
    for (const auto &char_and_width : j["widths"]) {
        std::string skey = char_and_width[0];
        char c = skey.data()[0];
        this->stride[c] = char_and_width[1];
        this->indices[c] = index;
        index ++;
    }
}

float Font::line_spacing() const
{
    return this->_line_spacing;
}

void Font::line_spacing(float v)
{
    this->_line_spacing = v;
}