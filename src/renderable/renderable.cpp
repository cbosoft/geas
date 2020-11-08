#include "../geas_object/geas_object.hpp"
#include "../renderer/renderer.hpp"
#include "../resourcemanager/resourcemanager.hpp"
#include "renderable.hpp"

Renderable::Renderable(GeasObject *parent)
    : Transform(parent)
    , has_texture(false)
    , frame_lower_bound(0)
    , frame_upper_bound(1)
    , frame_current(0)
    , has_colour(false)
    , colour(1.0)
    , size({10.0f, 10.0f})
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
    this->has_texture = true;
    this->texture_path = path;
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
    this->frame_current++;
    if ((this->frame_current >= this->frame_upper_bound) || (this->frame_current < this->frame_lower_bound)) {
        this->frame_current = this->frame_lower_bound;
    }

    return this->frame_current;
}