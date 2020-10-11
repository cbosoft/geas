#pragma once

#include "../vector/vector.hpp"
#include "../shader/shader.hpp"
#include "../texture/texture.hpp"
#include "globject.hpp"

class Quad: public GLObject {

  public:
    Quad();
    Quad(Vec3 tr, Vec3 br, Vec3 bl, Vec3 tl);
    Quad(Vec3 tr, Vec3 br, Vec3 bl, Vec3 tl, std::string texture_name);
    void update_vertices(Vec3 tr, Vec3 br, Vec3 bl, Vec3 tl);
    void update_texture(Texture &texture);
    void update_texture(std::string filename);

    bool draw(Window &win);

    static Quad *square(float sidelength, float z=0.0f);

  private:

    ShaderProgram shaderProgram;
    Texture texture;
    unsigned int buffer_id, indices_id, attrib_id;

    struct quad_vertex {
      float x;
      float y;
      float z;

      float r;
      float g;
      float b;
      float a;

      float s;
      float t;
    };
};
