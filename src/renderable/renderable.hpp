#pragma once

#include <list>
#include <map>

#include "../transform/transform.hpp"
#include "../util/json.hpp"

class GeasObject;
class Renderable final : public Transform {
    // TODO: thread safety!
public:
    Renderable(GeasObject *parent);
    ~Renderable() noexcept;

    void set_anim_loop(const std::string &name);
    void set_texture(const std::string &path);
    const std::string &texture_path() const;
    unsigned int increment_frame();
    unsigned int current_frame() const;
    bool has_texture() const;
    void set_animation_speed(float hz);
    void set_animation_period(unsigned int t);
    void set_animated(bool value);
    void set_frame(unsigned int i);

    Vec4 colour() const;
    void colour(const Vec4 &colour);

    Vec2 size() const;
    void size(const Vec2& s);

    void *data() const;
    void data(void *data);


private:
    void load_loops(const json &j);

    bool _has_texture;
    std::string _texture_path;
    unsigned int frame_lower_bound, frame_upper_bound, frame_current;
    bool animated;
    std::map<std::string, std::pair<unsigned int, unsigned int>> animation_loops;
    Vec4 _colour;
    Vec2 _size;
    void *renderer_data;
};