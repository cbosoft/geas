#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../resourcemanager/resourcemanager.hpp"
#include "../util/exception.hpp"
#include "rect.hpp"

Rect::Rect()
  :   anchor_mode(AnchorCentre)
    , animation_index(0)
    , animation_lb(0)
    , animation_ub(50)
    , inv_anim_speed(5)
    , framecount(0)
{
  unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3
  };

  vertices[0] = {/*  position: */ 1.0, 1.0, 0.0, /*  colour: */ 1.0, 1.0, 1.0, 1.0, /*  texture: */ 1.0, 1.0};
  vertices[1] = {/*  position: */ 1.0, 0.0, 0.0, /*  colour: */ 1.0, 1.0, 1.0, 1.0, /*  texture: */ 1.0, 0.0};
  vertices[2] = {/*  position: */ 0.0, 0.0, 0.0, /*  colour: */ 1.0, 1.0, 1.0, 1.0, /*  texture: */ 0.0, 0.0};
  vertices[3] = {/*  position: */ 0.0, 1.0, 0.0, /*  colour: */ 1.0, 1.0, 1.0, 1.0, /*  texture: */ 0.0, 1.0};

  glGenBuffers(1, &buffer_id);
  glGenBuffers(1, &indices_id);
  glGenVertexArrays(1, &attrib_id);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_id);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
  GLVertex *vertices_array = this->get_vertices_arr();
  glBufferData(GL_ARRAY_BUFFER, this->vertices.size()*sizeof(GLVertex), vertices_array, GL_STATIC_DRAW);

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

void Rect::update_texture(std::string filename)
{
  ResourceManager &rm = ResourceManager::singleton();
  Texture *t = rm.get_texture(filename);
  this->update_texture(t);
}

void Rect::update_texture(Texture *texture)
{
  this->texture = texture;
  std::cout << "texture id=" << this->texture->get_id() << std::endl;
}

void Rect::set_loop(std::string name)
{
  this->texture->request_animation_bounds(name, this->animation_lb, this->animation_ub);
}


bool Rect::draw()
{
  advance_animation();

  shaderProgram->use();
  texture->use();

  glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_id);
  glBindVertexArray(attrib_id);

  gl_error_check("Rect::draw(), after glBindVertexArray(...)");
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  gl_error_check("Rect::draw(), after glDrawElements(...)");
  return false;
}

void Rect::update_position(std::array<Vec3, 4> positions)
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

void Rect::update_position(Vec3 position)
{
  float sx = this->vertices[1].x - this->vertices[2].x;
  float sy = this->vertices[0].y - this->vertices[1].y;

  std::array<Vec3, 4> positions;
  // or change pos of centre?
  positions[0] = position + Vec3({ sx,  sy, 0.0}); // tr
  positions[1] = position + Vec3({ sx, 0.0, 0.0}); // br
  positions[2] = position + Vec3({0.0, 0.0, 0.0}); // bl
  positions[3] = position + Vec3({0.0,  sy, 0.0}); // tl
  this->update_position(positions);
}

void Rect::update_scale(float scale)
{
  float sx = (this->vertices[1].x - this->vertices[2].x)*scale;
  float sy = (this->vertices[0].y - this->vertices[1].y)*scale;
  Vec2 size({sx, sy});
  this->update_size(size);
}

void Rect::update_size(Vec2 size)
{
  switch(anchor_mode) {

    case AnchorCentre:
      this->update_size_from_centre(size);
      break;

    case AnchorBottomLeft:
      this->update_size_from_bl(size);
      break;
  }
}

void Rect::update_size_from_centre(Vec2 size)
{
  float cx = (this->vertices[2].x + this->vertices[1].x)*0.5;
  float cy = (this->vertices[0].y + this->vertices[1].y)*0.5;
  float cz = this->vertices[0].z;
  Vec3 centre({cx, cy, cz});

  float hsx = size.x()*0.5;
  float hsy = size.y()*0.5;

  std::array<Vec3, 4> positions;
  positions[0] = centre + Vec3({ hsx, hsy, 0.0}); // tr
  positions[1] = centre + Vec3({ hsx,-hsy, 0.0}); // br
  positions[2] = centre + Vec3({-hsx,-hsy, 0.0}); // bl
  positions[3] = centre + Vec3({-hsx, hsy, 0.0}); // tl
  this->update_position(positions);

}

void Rect::update_size_from_bl(Vec2 size)
{
  float blx = this->vertices[2].x;
  float bly = this->vertices[2].y;
  float blz = this->vertices[2].z;
  Vec3 bl({blx, bly, blz});

  float sx = size.x();
  float sy = size.y();

  std::array<Vec3, 4> positions;
  positions[0] = bl + Vec3({ sx,   sy, 0.0}); // tr
  positions[1] = bl + Vec3({ sx,  0.0, 0.0}); // br
  positions[2] = bl + Vec3({ 0.0, 0.0, 0.0}); // bl
  positions[3] = bl + Vec3({ 0.0,  sy, 0.0}); // tl
  this->update_position(positions);

}

void Rect::update_texture_coords(std::array<Vec2, 4> texcoords)
{
  for (int i = 0; i < 4; i++) {
    this->vertices[i].s = texcoords[i].x();
    this->vertices[i].t = texcoords[i].y();
  }

  GLVertex *vertices_array = this->get_vertices_arr();
  glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
  glBufferData(GL_ARRAY_BUFFER, this->vertices.size()*sizeof(GLVertex), vertices_array, GL_STATIC_DRAW);
}

Rect *Rect::square(float sidelength, float z)
{
  float hs = sidelength/2;
  Rect *rv = new Rect();

  rv->update_position({
      Vec3({ hs,  hs, z}),
      Vec3({ hs, -hs, z}),
      Vec3({-hs, -hs, z}),
      Vec3({-hs,  hs, z})
      }
  );

  return rv;
}

GLVertex *Rect::get_vertices_arr()
{
  return this->vertices.data();
}

void Rect::advance_animation()
{
  framecount ++;

  //std::cout << "next frame " << animation_index << " " << framecount << std::endl;
  if (framecount > this->inv_anim_speed) {
    framecount = 0;
    this->animation_index++;
    if (this->animation_index >= this->animation_ub) {
      this->animation_index = this->animation_lb;
    }

    float inv_n = this->texture->get_inv_n_frames();
    float xstart = inv_n * float(this->animation_index);
    float xend = inv_n * float(this->animation_index + 1);
    this->update_texture_coords({
        Vec2({xend, 1.0}),
        Vec2({xend, 0.0}),
        Vec2({xstart, 0.0}),
        Vec2({xstart, 1.0})
        });
  }

}

void Rect::request_animation(std::string name)
{
  this->texture->request_animation_bounds(name, this->animation_lb, this->animation_ub);
  if (this->animation_index < this->animation_lb || this->animation_index >= this->animation_ub)
    this->animation_index = this->animation_lb;
}
