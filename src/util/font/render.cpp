#include <iostream>
#include "font.hpp"
#include "../../geas_object/tile/tile.hpp"

void Font::render_character(Transform *parent, char c, Vec2 &bl)
{
    auto *tile = new Tile(parent, this->height, this->texture_name);
    tile->set_variant(this->indices[c]);
    tile->relative_position(bl.promote(0.0f));
    bl.x(bl.x() + this->stride[c]);
    std::cerr << c << " " << this->stride[c] << std::endl;
}

void Font::render_word(Transform *parent, const std::string &word, Vec2 &bl)
{
    auto chars = word.data();
    for (unsigned int i = 0; i < word.size(); i++) {
        char c = chars[i];
        this->render_character(parent, c, bl);
    }
    bl.x(bl.x() + this->stride[' ']);
}


void Font::render_text(Transform *parent, const std::string &text, const Vec2 &size) {
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
        if (bl.x() + width > size.x()) {
            bl.y(bl.y() - this->height*this->_line_spacing);
            bl.x(0.0f);
        }
        this->render_word(parent, word, bl);
    }
}

float Font::word_length(const std::string &word)
{
    float width = 0.0f;
    auto chars = word.data();
    for (unsigned int i = 0; i < word.size(); i++) {
        char c = chars[i];
        width += this->stride[c];
    }
    return width;
}