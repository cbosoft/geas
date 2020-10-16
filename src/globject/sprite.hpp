#pragma once

#include <array>

#include "../vector/vector.hpp"
#include "../shader/shader.hpp"
#include "../texture/texture.hpp"
#include "globject.hpp"
#include "glvertex.hpp"

enum AnchorMode { AnchorCentre, AnchorBottomLeft };

class Sprite: public GLObject {

  public:
    Sprite(std::string texture);

    void request_animation(std::string name);

    void update_texture(std::string filename);
    void update_texture(Texture *texture);

    void update_vertices(std::array<GLVertex,4> vertices);
    void update_position(Vec3 bl);
    void update_scale(float scale);
    void update_size(Vec2 size);
    void update_size_from_centre(Vec2 size);
    void update_size_from_bl(Vec2 size);
    void update_position(std::array<Vec3, 4> positions);
    void update_colour(std::array<Vec4, 4> colours);
    void update_texture_coords(std::array<Vec2, 4> texcoords);

    void set_loop(std::string name);

    bool draw() override;

  private:

    GLVertex *get_vertices_arr();
    void advance_animation();

    ShaderProgram *shaderProgram;
    Texture *texture;

    AnchorMode anchor_mode;
    std::array<GLVertex, 4> vertices;
    unsigned int buffer_id, indices_id, attrib_id;

    unsigned int animations_frames, animation_index, animation_lb, animation_ub, inv_anim_speed, framecount;
};
