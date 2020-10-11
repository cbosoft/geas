#include <iostream>
#include <ctime>

#include "window/window.hpp"
#include "globject/globject.hpp"
#include "resourcemanager/resourcemanager.hpp"

static unsigned int compile_shader(unsigned int type, const std::string& source)
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
    char msg[len];
    glGetShaderInfoLog(id, len, &len, msg);
    std::cout << "Failed to compile shader." << std::endl;
    std::cout << msg << std::endl;
    glDeleteShader(id);
    return 0;
  }

  return id;
}

static unsigned int create_shader(const std::string& vertex_shader, const std::string& fragment_shader)
{
  unsigned int prog_id = glCreateProgram();
  unsigned int vs = compile_shader(GL_VERTEX_SHADER, vertex_shader);
  unsigned int fs = compile_shader(GL_FRAGMENT_SHADER, fragment_shader);

  glAttachShader(prog_id, vs);
  glAttachShader(prog_id, fs);
  glLinkProgram(prog_id);
  glValidateProgram(prog_id);

  // should detach shader
  glDeleteShader(vs);
  glDeleteShader(fs);

  return prog_id;//?
}

class TestGLObject final : public virtual GLObject
{
  public:

    TestGLObject() {

      static float positions[6] = {
        -0.5f, -0.5f,
         0.0f,  0.5f,
         0.5f, -0.5f
      };

      glGenBuffers(1, &buffer_id);
      glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
      glBufferData(GL_ARRAY_BUFFER, 6*sizeof(float), positions, GL_STATIC_DRAW);

      glGenVertexArrays(1, &attrib_id);
      glBindVertexArray(attrib_id);
      glEnableVertexAttribArray(0);
      glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
      glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), 0);

      ResourceManager &rm = ResourceManager::GetSingleton();
      std::string vs_source = rm.read_text_file("shaders/simple_vertex.glsl");
      std::string fs_source = rm.read_text_file("shaders/simple_fragment.glsl");
      unsigned int shader = create_shader(vs_source, fs_source);
      glUseProgram(shader);
    }

    bool draw(Window &win) override
    {

      (void) win;

      glDrawArrays(GL_TRIANGLES, 0, 3);

      return false;
    }

  private:

    unsigned int buffer_id, attrib_id;
};

int main(void)
{
  Window &w = window(640, 480, "geas");

  w.push_object(new TestGLObject());
  w.run();
}
