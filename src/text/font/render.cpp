#include <iostream>
#include "font.hpp"
#include "../../geas_object/tile/tile.hpp"
#include "../glyph/glyph.hpp"

void Font::render_character(Transform *parent, std::vector<Glyph *> &glyphs, char c, Vec2 &bl, unsigned int &char_index) const
{
    Glyph *glyph = nullptr;
    if (char_index >= glyphs.size()) {
        glyph = new Glyph(parent, this);
        glyphs.push_back(glyph);
    }
    else {
        glyph = glyphs[char_index];
    }
    glyph->set_char(c);
    glyph->relative_position(bl.promote(0.0f));
    bl.x(bl.x() + this->get_stride_of(c)*this->_scale);
    char_index++;
}

void Font::render_word(Transform *parent, std::vector<Glyph *> &glyphs, const std::string &word, Vec2 &bl, unsigned int &char_index) const
{
    auto chars = word.data();
    for (unsigned int i = 0; i < word.size(); i++) {
        char c = chars[i];
        this->render_character(parent, glyphs, c, bl, char_index);
    }
    this->render_character(parent, glyphs, ' ', bl, char_index);
}


void Font::render_text(Transform *t, std::vector<Glyph *> &glyphs, const std::string &text) const
{
    auto chars = text.data();
    Vec2 bl;
    unsigned int char_index = 0;
    for (unsigned int i = 0; i < text.size(); i++) {
        this->render_character(t, glyphs, chars[i], bl, char_index);
    }
    for (unsigned int i = char_index; i < glyphs.size(); i++) {
        glyphs[i]->set_char(' ');
    }
}


void Font::render_text(Transform *parent, std::vector<Glyph *> &glyphs, const std::string &text, const Vec2 &size) const
{
    auto chars = text.data();
    std::list<Vec2> positions;
    std::list<std::string> words;
    {
        std::string word;
        for (unsigned int i = 0; i < text.size(); i++) {
            char c = chars[i];
            if (c == ' ') {
                if (!word.empty()) {
                    words.push_back(word);
                    word = "";
                }
            } else {
                word += c;
            }
        }

        if (!word.empty())
            words.push_back(word);
    }

    unsigned int char_index = 0;
    Vec2 bl;
    for (const auto &word : words) {
        float width = this->word_length(word);
        std::cerr << width << " " << bl.x() << " " << size.x() << std::endl;
        if (bl.x() + width > size.x()) {
            bl.y(bl.y() - this->_height*this->_line_spacing*this->_scale);
            bl.x(0.0f);
        }
        this->render_word(parent, glyphs, word, bl, char_index);
    }

    for (unsigned int i = char_index; i < glyphs.size(); i++) {
        glyphs[i]->set_char(' ');
    }
}

float Font::word_length(const std::string &word) const
{
    float width = 0.0f;
    auto chars = word.data();
    for (unsigned int i = 0; i < word.size(); i++) {
        char c = chars[i];
        width += this->get_stride_of(c)*this->_scale;
    }
    return width;
}
