#pragma once

#include "../vector/vector.hpp"
#include "globject.hpp"
#include "../shader/shader.hpp"

class GLTriangle final : public GLObject {

  public:
    GLTriangle(Vec2 a, Vec2 b, Vec2 c);

    bool draw(Window &win);

  private:

    ShaderProgram shaderProgram;
    unsigned int buffer_id, attrib_id;
};
