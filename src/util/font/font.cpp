#include <iostream>
#include "../../resourcemanager/resourcemanager.hpp"
#include "../json.hpp"
#include "font.hpp"

Font::Font(const std::string &font_sheet)
    : texture_name(font_sheet)
    , height(16.0f)
    , _line_spacing(1.5f)
    , _scale(1.0f)
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

float Font::scale() const
{
    return this->_scale;
}

void Font::scale(float v)
{
    this->_scale = v;
}


float Font::get_stride_of(char c) const
{
    auto it = this->stride.find(c);
    if (it != this->stride.end()) {
        return it->second;
    }
    return 16.0f;
}


unsigned int Font::get_index_of(char c) const
{
    auto it = this->indices.find(c);
    if (it != this->indices.end()) {
        return it->second;
    }
    return 0;
}