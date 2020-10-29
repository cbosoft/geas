#pragma once

#include <string>

class Shader {
  public:
    Shader();
    ~Shader();
    Shader(const Shader &other)
    {
      this->shader_id = other.shader_id;
      this->type = other.type;
    }
    Shader &operator=(const Shader &other)
    {
      this->shader_id = other.shader_id;
      this->type = other.type;
      return *this;
    }

    static Shader from_source(unsigned int type, std::string source_string);
    static Shader from_file(std::string filename);

    unsigned int get_id() const;

  private:

    static unsigned int compile_source_to_shader(unsigned int type, std::string source);
    unsigned int shader_id, type;
};
