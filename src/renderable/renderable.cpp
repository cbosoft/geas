#include <iostream>

#include "../renderer/renderer.hpp"
#include "../resourcemanager/resourcemanager.hpp"
#include "renderable.hpp"

Renderable::Renderable(Transform *parent)
    : Transform(parent)
    , _current_frame(0)
    , _layer(0)
    , _has_texture(false)
    , _colour(1.0)
    , _size({16.0f, 16.0f})
    , renderer_data(nullptr)
    , _texture_changed(false)
{

}

Renderable::~Renderable() noexcept
{
    if (this->renderer_data) {
        Renderer *rend = Renderer::get(nullptr);
        rend->clean(this);
    }
}


Vec2 Renderable::size() const
{
    return this->_size*1.001f;
}

void Renderable::size(const Vec2 &size)
{
    this->_size = size;
}

Vec4 Renderable::colour() const
{
    return this->_colour;
}

void Renderable::colour(const Vec4 &colour)
{
    this->_colour = colour;
}

bool Renderable::has_texture() const
{
    return this->_has_texture;
}

void *Renderable::data() const
{
    return this->renderer_data;
}

void Renderable::data(void *data)
{
    this->renderer_data = data;
}

const std::string &Renderable::texture_path() const
{
    return this->_texture_path;
}

void Renderable::set_texture(const std::string &path)
{
    this->_has_texture = true;
    this->_texture_path = path;
    this->_texture_changed = true;
}

unsigned int Renderable::current_frame() const
{
    return this->_current_frame;
}

void Renderable::current_frame(unsigned int i)
{
    this->_current_frame = i;
}

unsigned int Renderable::layer() const
{
    return this->_layer;
}

void Renderable::layer(unsigned int i)
{
    this->_layer = i;
}

void Renderable::set_texture_cached()
{
    this->_texture_changed = false;
}

bool Renderable::texture_changed() const
{
    return this->_texture_changed;
}
