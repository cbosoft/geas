#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../resourcemanager/resourcemanager.hpp"
#include "quad.hpp"

Quad::Quad()
{
  unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3
  };

  glGenBuffers(1, &buffer_id);
  glGenBuffers(1, &indices_id);
  glGenVertexArrays(1, &attrib_id);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_id);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

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

Quad::Quad(Vec3 tr, Vec3 br, Vec3 bl, Vec3 tl)
  : Quad()
{
  update_vertices(tr, br, bl, tl);
}

Quad::Quad(Vec3 tr, Vec3 br, Vec3 bl, Vec3 tl, std::string texture_file)
  : Quad(tr, br, bl, tl)
{
  this->update_texture(texture_file);
}

void Quad::update_texture(std::string filename)
{
  ResourceManager &rm = ResourceManager::singleton();
  Texture t = rm.get_texture(filename);
  this->update_texture(t);
}

void Quad::update_texture(Texture &texture)
{
  this->texture = texture;
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

void Quad::update_vertices(Vec3 tr, Vec3 br, Vec3 bl, Vec3 tl)
{
  glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
  struct quad_vertex vertices[4] = {
    {tr.x(), tr.y(), tr.z(),   1.0, 1.0, 1.0, 1.0,   1.0, 1.0},
    {br.x(), br.y(), br.z(),   1.0, 1.0, 1.0, 1.0,   1.0, 0.0},
    {bl.x(), bl.y(), bl.z(),   1.0, 1.0, 1.0, 1.0,   0.0, 0.0},
    {tl.x(), tl.y(), tl.z(),   1.0, 1.0, 1.0, 1.0,   0.0, 1.0}
  };
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

Quad *Quad::square(float sidelength, float z)
{
  float hs = sidelength/2;
  return new Quad(
      Vec3({ hs,  hs, z}),
      Vec3({ hs, -hs, z}),
      Vec3({-hs, -hs, z}),
      Vec3({-hs,  hs, z})
  );
}
