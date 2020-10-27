#include <regex>
#include <iostream>
#include <map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../../../util/exception.hpp"
#include "../../../resourcemanager/resourcemanager.hpp"
#include "shader.hpp"

Shader::Shader()
{
}

Shader::~Shader()
{
}

unsigned int Shader::get_id() const
{
  return this->shader_id;
}

Shader Shader::from_source(unsigned int type, std::string source)
{
  Shader shader;
  shader.shader_id = Shader::compile_source_to_shader(type, source);
  shader.type = type;
  return shader;
}

Shader Shader::from_file(std::string filename)
{
  std::string source = ResourceManager::singleton().read_text_file(filename);

  unsigned int type = GL_VERTEX_SHADER;
  bool assigned = false;
  static std::map<unsigned int, std::regex> type_and_re = {
    std::make_pair(GL_VERTEX_SHADER, std::regex(".*_vert\\.glsl")),
    std::make_pair(GL_FRAGMENT_SHADER, std::regex(".*_frag\\.glsl"))
  };

  for (auto kv: type_and_re) {
    auto maybe_type = kv.first;
    auto re = kv.second;

    if (std::regex_match(filename, re)) {
      type = maybe_type;
      assigned = true;
      break;
    }
  }

  if (!assigned) {
    throw ShaderError(Formatter() << "Could not determine shader type from file name \"" << filename << "\".");
  }

  return Shader::from_source(type, source);
}

unsigned int Shader::compile_source_to_shader(unsigned int type, std::string source)
{
  unsigned int id = glCreateShader(type);
  const char *c_source = source.c_str();
  glShaderSource(id, 1, &c_source, nullptr);
  glCompileShader(id);

  int res;
  glGetShaderiv(id, GL_COMPILE_STATUS, &res);

  if (res == GL_FALSE) {
    // compile error :(
    int len;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);

    char *msg = (char *)alloca(len);
    glGetShaderInfoLog(id, len, &len, msg);
    glDeleteShader(id);
    throw ShaderCompileError(Formatter() << "Failed to compile shader: " << &(msg[0]));
  }

  return id;
}
