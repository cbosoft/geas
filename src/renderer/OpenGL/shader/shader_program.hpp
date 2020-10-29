#pragma once

#include <string>
#include <vector>

class Shader;
class ShaderProgram {

public:
    ~ShaderProgram();

    static ShaderProgram *from_file(std::string vert_source_path, std::string frag_source_path);
    void set_uniform(const char *name, float value) const;
    void set_uniform(const std::string &name, float value) const;

    void use();

private:

    ShaderProgram();
    unsigned int link();
    void add_shader(const Shader &shader);

    bool linked;
    unsigned int prog_id;
    std::vector<unsigned int> attached_shaders;
};
