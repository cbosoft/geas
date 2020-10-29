#include <GL/glew.h>

#include "../../../util/exception.hpp"
#include "../../../util/debug.hpp"

#include "shader.hpp"
#include "shader_program.hpp"

ShaderProgram::ShaderProgram()
{
    this->prog_id = glCreateProgram();
    debug_msg(Formatter() << "Created new gl shader program " << this->prog_id);
    GL_ERROR_CHECK_DBG("ShaderProgram::link() -> before link");
    this->linked = false;
}

ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(this->prog_id);
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

        debug_msg(Formatter() << "program " << this->prog_id << " linking");
        GL_ERROR_CHECK_DBG("ShaderProgram::link() -> before link");
        glLinkProgram(this->prog_id);
        GL_ERROR_CHECK_DBG("ShaderProgram::link() -> after link, before validate");
        glValidateProgram(this->prog_id);
        GL_ERROR_CHECK_DBG("ShaderProgram::link() -> after validate");

        int is_linked = 0;
        glGetProgramiv(this->prog_id, GL_LINK_STATUS, &is_linked);
        if (is_linked != GL_TRUE)
        {
            // On link error, try to find out what went wrong.
            int max_length = 100;
            glGetProgramiv(this->prog_id, GL_INFO_LOG_LENGTH, &max_length);

            char *info = (char *)alloca(max_length*sizeof(char));
            
            glGetProgramInfoLog(this->prog_id, max_length, &max_length, info);

            if (max_length == 0) {
                throw ShaderError(Formatter() << "Shader linking error. No extra information on this was provided by OpenGL. Helpful. ");
            }
            else {
                throw ShaderError(Formatter() << "Shader linking error: '" << info << "' ");
            }
        }


        this->linked = true;
        debug_msg(Formatter() << "shader program " << this->prog_id << " linked");

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
