#include <iostream>

#include <GL/glew.h>

#include "../../../util/exception.hpp"

#include "texture.hpp"

Texture::Texture(const ImageData &image)
    :   glid(0)
    ,   _number_frames_x(image.number_frames_x())
    ,   _number_frames_y(image.number_frames_y())
    ,   _number_layers(image.number_layers())
{
    glGenTextures(1, &this->glid);
    glBindTexture(GL_TEXTURE_2D, this->glid);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    unsigned int imtype = image.number_channels() == 3?GL_RGB:GL_RGBA;
    glTexImage2D(GL_TEXTURE_2D,
        0,
        imtype,
        image.width(),
        image.height(),
        0,
        imtype,
        GL_UNSIGNED_BYTE,
        image.data());

    glGenerateMipmap(GL_TEXTURE_2D);

    this->framewidth = 1.0f/static_cast<float>(this->_number_frames_x);
    this->frameheight = 1.0f/static_cast<float>(this->_number_frames_y*this->_number_layers);
    GL_ERROR_CHECK_DBG("Texture::Texture(), constructor end");
}

Vec4 Texture::get_rect(unsigned int l, unsigned int i) const
{
    unsigned int r = i / this->_number_frames_x;
    unsigned int c = i % this->_number_frames_x;
    return this->get_rect(l, r, c);
}

Vec4 Texture::get_rect(unsigned int l, unsigned int r, unsigned int c) const
{
    float y = this->frameheight * static_cast<float>(r + (this->_number_layers - l - 1)*this->_number_frames_y);
    float x = this->framewidth * static_cast<float>(c);
    return Vec4({x, y, this->framewidth, this->frameheight});
}

void Texture::use() const
{
    GL_ERROR_CHECK_DBG("Texture::use(), before use");
    glBindTexture(GL_TEXTURE_2D, this->glid);
    GL_ERROR_CHECK_DBG("Texture::use(), after use");
}
