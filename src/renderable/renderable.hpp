#pragma once

#include <list>
#include <map>

#include "../transform/transform.hpp"
#include "../util/json.hpp"

class GeasObject;
class Renderable final : public Transform {
    // TODO: thread safety!
    // TODO TIDY UP THIS JANKY MESS
public:
    Renderable(GeasObject *parent);
    ~Renderable() noexcept;


    bool has_texture;
    std::string texture_path;
    unsigned int frame_lower_bound, frame_upper_bound, frame_current;
    std::map<std::string, std::pair<unsigned int, unsigned int>> animation_loops;

    bool has_colour;
    Vec4 colour;

    Vec2 size;

    void *renderer_data;

    void set_anim_loop(const std::string &name);
    void load_loops(const json &j);
    void set_texture(const std::string &path);
    unsigned int increment_frame();

};