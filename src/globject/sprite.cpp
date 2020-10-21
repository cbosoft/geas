#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../resourcemanager/resourcemanager.hpp"
#include "../util/exception.hpp"
#include "../camera/camera.hpp"
#include "../util/debug.hpp"
#include "sprite.hpp"

Sprite::Sprite(Transform *parent, const std::string& texture_path)
  :   Transform(parent)
    , anchor_mode(AnchorCentre)
    , animation_index(0)
    , animation_lb(0)
    , animation_ub(50)
    , inv_anim_speed(5)
    , framecount(0)
    , vertices_invalid_p(false)
{
  unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3
  };

  vertices[0] = {/*  position: */ 1.0, 1.0, 0.0, /*  colour: */ 1.0, 1.0, 1.0, 1.0, /*  texture: */ 1.0, 1.0};
  vertices[1] = {/*  position: */ 1.0, 0.0, 0.0, /*  colour: */ 1.0, 1.0, 1.0, 1.0, /*  texture: */ 1.0, 0.0};
  vertices[2] = {/*  position: */ 0.0, 0.0, 0.0, /*  colour: */ 1.0, 1.0, 1.0, 1.0, /*  texture: */ 0.0, 0.0};
  vertices[3] = {/*  position: */ 0.0, 1.0, 0.0, /*  colour: */ 1.0, 1.0, 1.0, 1.0, /*  texture: */ 0.0, 1.0};

  // TODO: split GL stuff out from sprite: push into texture?
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

  if (!texture_path.empty()) {
    texture = ResourceManager::singleton().get_texture(texture_path);
    shaderProgram = ShaderProgram::from_file("shaders/simple_vert.glsl", "shaders/simple_texture_frag.glsl");
  }
  else {
    texture = nullptr;
    shaderProgram = ShaderProgram::from_file("shaders/simple_vert.glsl", "shaders/simple_blockcolour_frag.glsl");
  }
}

Sprite::Sprite(Transform *parent, const std::string &texture_path, const Vec2 &size)
  : Sprite(parent, texture_path)
{
  this->update_size(size);
}

void Sprite::update_texture(std::string filename)
{
  ResourceManager &rm = ResourceManager::singleton();
  Texture *t = rm.get_texture(filename);
  this->update_texture(t);
}

void Sprite::update_texture(Texture *texture)
{
  this->texture = texture;
  std::cout << "texture id=" << this->texture->get_id() << std::endl;
}

void Sprite::set_loop(std::string name)
{
  this->texture->request_animation_bounds(name, this->animation_lb, this->animation_ub);
}


bool Sprite::draw()
{
    advance_animation();

    {
        Vec3 abspos = this->absolute_position();
        if (this->position_cache != abspos || this->position_cache_unset) {
            this->position_cache = abspos;
            this->position_cache_unset = false;
            this->update_position(abspos);
        }
    }

    if (this->vertices_invalid_p) {
        // TODO: also check if parent transform has moved
        GLVertex *vertices_array = this->get_vertices_arr();
        //for (auto vertex : this->vertices) {
        //    debug_msg(Formatter() << " drawing vertex " << vertex.x << "," << vertex.y );
        //}

        glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
        glBufferData(GL_ARRAY_BUFFER, this->vertices.size()*sizeof(GLVertex), vertices_array, GL_STATIC_DRAW);
        this->vertices_invalid_p = false;
    }

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

void Sprite::update_position(const Vec3 &position)
{
    switch (this->anchor_mode) {
        case AnchorBottomLeft:
            this->update_position_bl(position);
            break;
        case AnchorCentre:
            this->update_position_centre(position);
            break;
    }
}

void Sprite::update_position_bl(const Vec3 &position)
{
    Vec2 size = this->get_size();
    float sx = size.x();
    float sy = size.y();

    std::array<Vec3, 4> positions;
    positions[0] = position + Vec3({ sx,  sy, 0.0}); // tr
    positions[1] = position + Vec3({ sx, 0.0, 0.0}); // br
    positions[2] = position + Vec3({0.0, 0.0, 0.0}); // bl
    positions[3] = position + Vec3({0.0,  sy, 0.0}); // tl
    this->update_position(positions);
}

void Sprite::update_position_centre(const Vec3 &position)
{
    Vec2 half_size = this->get_size() * 0.5f;
    float hsx = half_size.x();
    float hsy = half_size.y();

    std::array<Vec3, 4> positions;
    positions[0] = position + Vec3({ hsx,  hsy, 0.0}); // tr
    positions[1] = position + Vec3({ hsx, -hsy, 0.0}); // br
    positions[2] = position + Vec3({-hsx, -hsy, 0.0}); // bl
    positions[3] = position + Vec3({-hsx,  hsy, 0.0}); // tl
    this->update_position(positions);
}

void Sprite::update_position(std::array<Vec3, 4> positions)
{
    for (int i = 0; i < 4; i++) {
        Vec3 pos_in_world = Camera::main()->world_to_window(positions[i]);
        this->vertices[i].x = pos_in_world.x();
        this->vertices[i].y = pos_in_world.y();
        this->vertices[i].z = pos_in_world.z();
    }
    this->vertices_invalid_p = true;
}

void Sprite::update_scale(const Vec2 &scale)
{
    Vec2 size = this->get_size() * scale;
    this->update_size(size);
}

void Sprite::update_size(const Vec2& size)
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

void Sprite::update_size_from_centre(const Vec2& size)
{
  Vec3 centre = this->get_centre().promote(this->vertices[0].z);

  float hsx = size.x()*0.5f;
  float hsy = size.y()*0.5f;

  std::array<Vec3, 4> positions;
  positions[0] = centre + Vec3({ hsx, hsy, 0.0}); // tr
  positions[1] = centre + Vec3({ hsx,-hsy, 0.0}); // br
  positions[2] = centre + Vec3({-hsx,-hsy, 0.0}); // bl
  positions[3] = centre + Vec3({-hsx, hsy, 0.0}); // tl
  this->update_position(positions);

}

void Sprite::update_size_from_bl(const Vec2 &size)
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

void Sprite::update_texture_coords(std::array<Vec2, 4> texcoords)
{
  for (int i = 0; i < 4; i++) {
    this->vertices[i].s = texcoords[i].x();
    this->vertices[i].t = texcoords[i].y();
  }
  this->vertices_invalid_p = true;
}

GLVertex *Sprite::get_vertices_arr()
{
  return this->vertices.data();
}

void Sprite::advance_animation()
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

void Sprite::request_animation(std::string name)
{
  this->texture->request_animation_bounds(name, this->animation_lb, this->animation_ub);
  if (this->animation_index < this->animation_lb || this->animation_index >= this->animation_ub)
    this->animation_index = this->animation_lb;
}

void Sprite::relative_position(const Vec3 &rel_pos)
{
    Transform::relative_position(rel_pos);
    Vec3 abs = this->absolute_position();
    Vec3 win = Camera::main()->world_to_window(abs);
    this->update_position(win);
}

void Sprite::local_scale(const Vec2 &scale)
{
    this->update_scale(scale);
    Transform::local_scale(scale);
}

Vec2 Sprite::get_size() const
{
    // TODO: don't get from the vertices, hold a 'master' copy of the size (in world units) for comparison with local scale
    float sx = this->vertices[1].x - this->vertices[2].x;
    float sy = this->vertices[0].y - this->vertices[1].y;
    Vec2 size_win({sx, sy});
    Vec2 size_world = Camera::main()->window_to_world(size_win);
    return size_world;
}

Vec2 Sprite::get_centre() const
{
    float cx = (this->vertices[0].x - this->vertices[2].x)*0.5f;
    float cy = (this->vertices[0].y - this->vertices[2].y)*0.5f;
    Vec2 centre_win({cx, cy});
    Vec2 centre_world = Camera::main()->window_to_world(centre_win);
    return centre_world;
}