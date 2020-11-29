#include <iostream>
#include "font.hpp"
#include "../../geas_object/tile/tile.hpp"

void Font::render_character(Transform *parent, char c, Vec2 &bl) const
{
    auto *tile = new Tile(parent, this->height*this->_scale, this->texture_name);
    tile->set_variant(0, this->get_index_of(c));
    tile->local_scale(Vec2(this->_scale));
    tile->relative_position(bl.promote(0.0f));
    bl.x(bl.x() + this->get_stride_of(c)*this->_scale);
}

void Font::render_word(Transform *parent, const std::string &word, Vec2 &bl) const
{
    auto chars = word.data();
    for (unsigned int i = 0; i < word.size(); i++) {
        char c = chars[i];
        this->render_character(parent, c, bl);
    }
    this->render_character(parent, ' ', bl);
}


void Font::render_text(Transform *t, const std::string &text) const
{
    auto chars = text.data();
    Vec2 bl;
    for (unsigned int i = 0; i < text.size(); i++) {
        this->render_character(t, chars[i], bl);
    }
}


void Font::render_text(Transform *parent, const std::string &text, const Vec2 &size) const
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

    Vec2 bl;
    for (const auto &word : words) {
        float width = this->word_length(word);
        std::cerr << width << " " << bl.x() << " " << size.x() << std::endl;
        if (bl.x() + width > size.x()) {
            bl.y(bl.y() - this->height*this->_line_spacing*this->_scale);
            bl.x(0.0f);
        }
        this->render_word(parent, word, bl);
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
