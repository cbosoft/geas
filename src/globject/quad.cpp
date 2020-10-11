#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../resourcemanager/resourcemanager.hpp"
#include "quad.hpp"

Quad::Quad(Vec2 a, Vec2 b, Vec2 c, Vec2 d)
{
  (void) a;
  (void) b;
  (void) c;
  (void) d;
  struct quad_vertex vertices[4] = {
   /*  X     Y    Z      R    G    B    A      S    T   */
    { 0.5,  0.5, 0.0,   1.0, 0.0, 0.0, 1.0,   1.0, 1.0},
    { 0.5, -0.5, 0.0,   0.0, 1.0, 0.0, 1.0,   1.0, 0.0},
    {-0.5, -0.5, 0.0,   0.0, 1.0, 0.0, 1.0,   0.0, 0.0},
    {-0.5,  0.5, 0.0,   0.0, 1.0, 0.0, 1.0,   0.0, 1.0}
  };

  unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3
  };

  glGenBuffers(1, &buffer_id);
  glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glGenBuffers(1, &indices_id);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_id);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glGenVertexArrays(1, &attrib_id);
  glBindVertexArray(attrib_id);
  glBindBuffer(GL_ARRAY_BUFFER, buffer_id);

  size_t vsz = sizeof(struct quad_vertex);

  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vsz, 0);
  glEnableVertexAttribArray(0);

  // color attribute
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, vsz, (void *)(3*sizeof(float)));
  glEnableVertexAttribArray(1);

  // texture coord attribute
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, vsz, (void *)(7*sizeof(float)));
  glEnableVertexAttribArray(2);

  ResourceManager &rm = ResourceManager::singleton();
  Shader &vert = rm.get_shader("shaders/simple_vert.glsl");
  Shader &frag = rm.get_shader("shaders/simple_frag.glsl");
  shaderProgram.add_shader(vert);
  shaderProgram.add_shader(frag);

  texture = rm.get_texture("textures/test2.png");
}

bool Quad::draw(Window &win)
{
  (void) win;
  shaderProgram.use();
  texture.use();
  glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_id);
  glBindVertexArray(attrib_id);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  return false;
}

void Quad::update_vertices(Vec2 a, Vec2 b, Vec2 c, Vec2 d)
{
  (void) a;
  (void) b;
  (void) c;
  (void) d;
  // float positions[6] = {
  //   a.x(), a.y(),
  //   b.x(), b.y(),
  //   c.x(), c.y()
  // };
  // glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
  // glBufferData(GL_ARRAY_BUFFER, 6*sizeof(float), positions, GL_STATIC_DRAW);
}

