#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../resourcemanager/resourcemanager.hpp"
#include "../util/exception.hpp"
#include "quad.hpp"

Quad::Quad()
  : animation_index(0), animation_lb(0), animation_ub(50)
{
  unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3
  };

  vertices[0] = {/*  position: */ 0.0, 0.0, 0.0, /*  colour: */ 1.0, 1.0, 1.0, 1.0, /*  texture: */ 1.0, 1.0};
  vertices[1] = {/*  position: */ 0.0, 0.0, 0.0, /*  colour: */ 1.0, 1.0, 1.0, 1.0, /*  texture: */ 1.0, 0.0};
  vertices[2] = {/*  position: */ 0.0, 0.0, 0.0, /*  colour: */ 1.0, 1.0, 1.0, 1.0, /*  texture: */ 0.0, 0.0};
  vertices[3] = {/*  position: */ 0.0, 0.0, 0.0, /*  colour: */ 1.0, 1.0, 1.0, 1.0, /*  texture: */ 0.0, 1.0};

  glGenBuffers(1, &buffer_id);
  glGenBuffers(1, &indices_id);
  glGenVertexArrays(1, &attrib_id);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_id);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glBindVertexArray(attrib_id);
  glBindBuffer(GL_ARRAY_BUFFER, buffer_id);

  size_t vsz = sizeof(GLVertex);

  // position attribute
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vsz, 0);
  glEnableVertexAttribArray(0);

  // color attribute
  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, vsz, (void *)(3*sizeof(float)));
  glEnableVertexAttribArray(1);

  // texture coord attribute
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, vsz, (void *)(7*sizeof(float)));
  glEnableVertexAttribArray(2);

  shaderProgram = ShaderProgram::from_file("shaders/simple_vert.glsl", "shaders/simple_frag.glsl");
  texture = ResourceManager::singleton().get_texture("textures/test2.png");
}

void Quad::update_texture(std::string filename)
{
  ResourceManager &rm = ResourceManager::singleton();
  Texture *t = rm.get_texture(filename);
  this->update_texture(t);
}

void Quad::update_texture(Texture *texture)
{
  this->texture = texture;
  std::cout << "texture id=" << this->texture->get_id() << std::endl;
}


bool Quad::draw(Window &win)
{
  (void) win;

  //advance_animation();

  shaderProgram->use();
  texture->use();

  glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_id);
  glBindVertexArray(attrib_id);
  gl_error_check("Quad::draw(), after glBindVertexArray(...)");
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  gl_error_check("Quad::draw(), after glDrawElements(...)");
  return false;
}

void Quad::update_position(std::array<Vec3, 4> positions)
{
  for (int i = 0; i < 4; i++) {
    this->vertices[i].x = positions[i].x();
    this->vertices[i].y = positions[i].y();
    this->vertices[i].z = positions[i].z();
  }

  GLVertex *vertices_array = this->get_vertices_arr();
  glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
  glBufferData(GL_ARRAY_BUFFER, this->vertices.size()*sizeof(GLVertex), vertices_array, GL_STATIC_DRAW);
}

void Quad::update_texture_coords(std::array<Vec2, 4> texcoords)
{
  for (int i = 0; i < 4; i++) {
    this->vertices[i].s = texcoords[i].x();
    this->vertices[i].t = texcoords[i].y();
  }

  GLVertex *vertices_array = this->get_vertices_arr();
  glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
  glBufferData(GL_ARRAY_BUFFER, this->vertices.size()*sizeof(GLVertex), vertices_array, GL_STATIC_DRAW);
}

Quad *Quad::square(float sidelength, float z)
{
  float hs = sidelength/2;
  Quad *rv = new Quad();

  rv->update_position({
      Vec3({ hs,  hs, z}),
      Vec3({ hs, -hs, z}),
      Vec3({-hs, -hs, z}),
      Vec3({-hs,  hs, z})
      }
  );

  return rv;
}

GLVertex *Quad::get_vertices_arr()
{
  return this->vertices.data();
}

void Quad::advance_animation()
{
  this->animation_index++;
  if (this->animation_index >= this->animation_ub) {
    this->animation_index = this->animation_lb;
  }


  float xstart = 0.02 * float(this->animation_index);
  float xend = 0.02 * float(this->animation_index + 1);
  std::cout << "next frame " << animation_index << " " << xstart << std::endl;
  this->update_texture_coords({
      Vec2({xend, 1.0}),
      Vec2({xend, 0.0}),
      Vec2({xstart, 0.0}),
      Vec2({xstart, 1.0})
      });
}
