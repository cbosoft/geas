#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../resourcemanager/resourcemanager.hpp"
#include "triangle.hpp"

GLTriangle::GLTriangle(Vec2 a, Vec2 b, Vec2 c)
{
  float positions[6] = {
    a.x(), a.y(),
    b.x(), b.y(),
    c.x(), c.y()
  };

  glGenBuffers(1, &buffer_id);
  glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
  glBufferData(GL_ARRAY_BUFFER, 6*sizeof(float), positions, GL_STATIC_DRAW);

  glGenVertexArrays(1, &attrib_id);
  glBindVertexArray(attrib_id);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), 0);

  ResourceManager &rm = ResourceManager::singleton();
  Shader &vert = rm.get_shader("shaders/simple_vert.glsl");
  Shader &frag = rm.get_shader("shaders/simple_frag.glsl");
  shaderProgram.add_shader(vert);
  shaderProgram.add_shader(frag);
}

bool GLTriangle::draw(Window &win)
{
  (void) win;
  glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
  glBindVertexArray(attrib_id);
  shaderProgram.use();
  glDrawArrays(GL_TRIANGLES, 0, 3);
  return false;
}
