#pragma once

#include <string>
#include <map>

#include "../../vector/vector.hpp"

class Transform;

class Font {
public:

    Font(const std::string &font_sheet);
    void render_text(Transform *t, const std::string &text, const Vec2 &size);
    [[nodiscard]] float line_spacing() const;
    void line_spacing(float v);

    [[nodiscard]] float scale() const;
    void scale(float v);

private:

    void render_character(Transform *t, char c, Vec2 &bl);
    void render_word(Transform *t, const std::string &w, Vec2 &bl);
    float word_length(const std::string &word);
    std::map<char, float> stride;
    std::map<char, unsigned int> indices;
    std::string texture_name;
    float height, _line_spacing, _scale;
};