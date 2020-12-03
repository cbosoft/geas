#pragma once

#include <string>
#include <map>
#include <vector>

#include "../../vector/vector.hpp"
#include "../../transform/transform.hpp"

class Glyph;

class Font {
public:

    explicit Font(const std::string &font_sheet);
    void render_text(Transform *t, std::vector<Glyph *> &glyphs, const std::string &text, const Vec2 &size) const;
    void render_text(Transform *t, std::vector<Glyph *> &glyphs, const std::string &text) const;
    [[nodiscard]] float line_spacing() const;
    void line_spacing(float v);

    [[nodiscard]] float scale() const;
    void scale(float v);

    [[nodiscard]] float base_height() const;
    [[nodiscard]] float height() const;
    [[nodiscard]] float line_height() const;

    [[nodiscard]] const std::string &texture_name() const;
    [[nodiscard]] unsigned int get_index_of(char c) const;

private:

    void render_character(Transform *t, std::vector<Glyph *> &glyphs, char c, Vec2 &bl, unsigned int &i) const;
    void render_word(Transform *t, std::vector<Glyph *> &glyphs, const std::string &w, Vec2 &bl, unsigned int &i) const;
    [[nodiscard]] float word_length(const std::string &word) const;
    [[nodiscard]] float get_stride_of(char c) const;
    std::map<char, float> stride;
    std::map<char, unsigned int> indices;
    std::string _texture_name;
    float _height, _line_spacing, _scale;
};