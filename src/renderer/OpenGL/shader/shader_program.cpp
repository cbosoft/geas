#include <GL/glew.h>

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
  else
  {
    glAttachShader(prog_id, shader.get_id());
  }
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

ShaderProgram *ShaderProgram::from_file(std::string vert_source_path, std::string frag_source_path)
{
  ShaderProgram *rv = new ShaderProgram;
  rv->add_shader(Shader::from_file(vert_source_path));
  rv->add_shader(Shader::from_file(frag_source_path));
  rv->link();
  return rv;
}
