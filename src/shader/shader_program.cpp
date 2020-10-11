#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "shader.hpp"

ShaderProgram::ShaderProgram()
{
  this->prog_id = glCreateProgram();
  this->linked = false;
}

ShaderProgram::~ShaderProgram()
{
  // do nothing?
}

void ShaderProgram::add_shader(const Shader& shader)
{
  if (linked) {
    // cannot add shader after program is linked!
    // TODO: exception
  }

  glAttachShader(prog_id, shader.get_id());
}

unsigned int ShaderProgram::link()
{
  if (!linked) {
    glLinkProgram(prog_id);
    glValidateProgram(prog_id);
    // TODO delete/detach shaders?
    this->linked = true;
  }

  return this->prog_id;
}

void ShaderProgram::use()
{
  glUseProgram(this->link());
}
