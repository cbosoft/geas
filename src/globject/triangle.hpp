#pragma once

#include "../vector/vector.hpp"
#include "../shader/shader.hpp"
#include "../texture/texture.hpp"
#include "globject.hpp"

class GLTriangle: public GLObject {

  public:
    GLTriangle(Vec2 a, Vec2 b, Vec2 c);
    void update_vertices(Vec2 a, Vec2 b, Vec2 c);

    bool draw(Window &win);

  private:

    ShaderProgram shaderProgram;
    Texture texture;
    unsigned int buffer_id, attrib_id;
};
