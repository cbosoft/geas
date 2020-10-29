#include <GL/glew.h>

#include "../../../util/exception.hpp"

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
        throw ShaderError("Cannot add shader after program is linked!");
    }
    else
    {
        GL_ERROR_CHECK_DBG("ShaderProgram::add_shader(shader) -> before shader attach");
        glAttachShader(this->prog_id, shader.get_id());
        GL_ERROR_CHECK_DBG("ShaderProgram::add_shader(shader) -> after shader attach");
        this->attached_shaders.push_back(shader.get_id());
    }
}

unsigned int ShaderProgram::link()
{
    if (!this->linked) {
        GL_ERROR_CHECK_DBG("ShaderProgram::link() -> before link");
        glLinkProgram(prog_id);
        GL_ERROR_CHECK_DBG("ShaderProgram::link() -> after link, before validate");
        glValidateProgram(prog_id);
        GL_ERROR_CHECK_DBG("ShaderProgram::link() -> after validate");
        // TODO delete/detach shaders?
        this->linked = true;
        for (auto shader : this->attached_shaders) {
          glDetachShader(this->prog_id, shader);
        }
    }

    return this->prog_id;
}

void ShaderProgram::use()
{
    GL_ERROR_CHECK_DBG("ShaderProgram::use() -> before use program");
    glUseProgram(this->link());
    GL_ERROR_CHECK_DBG("ShaderProgram::link() -> after use program");
}

ShaderProgram *ShaderProgram::from_file(std::string vert_source_path, std::string frag_source_path)
{
  ShaderProgram *rv = new ShaderProgram;
  rv->add_shader(Shader::from_file(vert_source_path));
  rv->add_shader(Shader::from_file(frag_source_path));
  rv->link();
  return rv;
}
