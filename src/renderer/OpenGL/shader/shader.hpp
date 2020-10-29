#pragma once

#include <string>
#include <vector>

class Shader;
class ShaderProgram {

  public:
    ~ShaderProgram();

    static ShaderProgram *from_file(std::string vert_source_path, std::string frag_source_path);

    void use();

  private:

    ShaderProgram();
    unsigned int link();
    void add_shader(const Shader &shader);

    bool linked;
    unsigned int prog_id;
    std::vector<unsigned int> attached_shaders;
};

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
