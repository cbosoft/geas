#pragma once

#include "../vector/vector.hpp"
#include "../shader/shader.hpp"
#include "../texture/texture.hpp"
#include "globject.hpp"

class Quad: public GLObject {

  public:
    Quad(Vec2 a, Vec2 b, Vec2 c, Vec2 d);
    void update_vertices(Vec2 a, Vec2 b, Vec2 c, Vec2 d);
    void update_texture(Texture &texture);

    bool draw(Window &win);

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
