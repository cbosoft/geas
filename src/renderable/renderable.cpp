#include <iostream>

#include "../geas_object/geas_object.hpp"
#include "../renderer/renderer.hpp"
#include "../resourcemanager/resourcemanager.hpp"
#include "renderable.hpp"

Renderable::Renderable(GeasObject *parent)
    : Transform(parent)
    , _has_texture(false)
    , frame_lower_bound(0)
    , frame_upper_bound(1)
    , frame_current(0)
    , animated(false)
    , _colour(1.0)
    , _size({16.0f, 16.0f})
    , renderer_data(nullptr)
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

unsigned int Renderable::current_frame() const
{
    return this->frame_current;
}


void Renderable::set_anim_loop(const std::string &name)
{
    auto loop = this->animation_loops[name];
    this->frame_lower_bound = loop.first;
    this->frame_upper_bound = loop.second;
}

void Renderable::load_loops(const json &js_loops)
{
    // linter (clangd) erroneously gives error on json.items(). Ignore it.
    for (auto& [key, value] : js_loops.items()) {
        unsigned int lb = value[0];
        unsigned int ub = value[1];
        this->animation_loops[key] = std::make_pair(lb, ub);
    }
}

void Renderable::set_texture(const std::string &path)
{
    this->_has_texture = true;
    this->_texture_path = path;
    json metadata = ResourceManager::singleton().get_metadata(path);
    // linter (clangd) erroneously gives error on json.items(). Ignore it.
    for (auto& [key, value] : metadata.items()) {
        std::string s_key = std::string(key);
        if (s_key.compare("animation_loops") == 0) {
            this->load_loops(value);
        }
    }
}

unsigned int Renderable::increment_frame()
{
    if (!this->animated)
        return this->frame_current;

    this->frame_current++;

    if ((this->frame_current >= this->frame_upper_bound) || (this->frame_current < this->frame_lower_bound)) {
        this->frame_current = this->frame_lower_bound;
    }

    return this->frame_current;
}

void Renderable::set_animated(bool value)
{
    this->animated = value;
}

void Renderable::set_frame(unsigned int i)
{
    this->frame_current = i;
}