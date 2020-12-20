#pragma once

#include <list>
#include <map>

#include "../transform/transform.hpp"
#include "../util/json.hpp"

class Renderable final : public Transform {
    // TODO: thread safety!
public:
    Renderable(Transform *parent);
    ~Renderable() noexcept;

    void set_texture(const std::string &path);
    const std::string &texture_path() const;
    bool has_texture() const;

    Vec4 colour() const;
    void colour(const Vec4 &colour);

    Vec2 size() const;
    void size(const Vec2& s);

    void *data() const;
    void data(void *data);

    unsigned int current_frame() const;
    void current_frame(unsigned int i);

    unsigned int layer() const;
    void layer(unsigned int i);

    void set_texture_cached();
    bool texture_changed() const;

private:

    unsigned int _current_frame;
    unsigned int _layer;
    bool _has_texture;
    std::string _texture_path;
    Vec4 _colour;
    Vec2 _size;
    void *renderer_data;
    bool _texture_changed;
};