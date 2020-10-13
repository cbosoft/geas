#pragma once

#include <array>

#include "../vector/vector.hpp"
#include "../shader/shader.hpp"
#include "../texture/texture.hpp"
#include "globject.hpp"
#include "glvertex.hpp"

class Quad: public GLObject {

  public:
    Quad();
    void update_texture(std::string filename);
    void update_texture(Texture *texture);

    void update_vertices(std::array<GLVertex,4> vertices);
    void update_position(std::array<Vec3, 4> positions);
    void update_colour(std::array<Vec4, 4> colours);
    void update_texture_coords(std::array<Vec2, 4> texcoords);

    bool draw(Window &win);

    static Quad *square(float sidelength, float z=0.0f);

  private:

    GLVertex *get_vertices_arr();
    void advance_animation();

    ShaderProgram *shaderProgram;
    Texture *texture;

    std::array<GLVertex, 4> vertices;
    unsigned int buffer_id, indices_id, attrib_id;

    unsigned int animations_frames, animation_index, animation_lb, animation_ub;
};
