#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "glerror.hpp"
#include "exception.hpp"

std::string glstrerror(unsigned int e)
{
  switch (e) {

    case GL_NO_ERROR:
      return "GL_NO_ERROR";

    case GL_INVALID_ENUM:
      return "GL_INVALID_ENUM";

    case GL_INVALID_VALUE:
      return "GL_INVALID_VALUE";

    case GL_INVALID_OPERATION:
      return "GL_INVALID_OPERATION";

    case GL_STACK_OVERFLOW:
      return "GL_STACK_OVERFLOW";

    case GL_STACK_UNDERFLOW:
      return "GL_STACK_UNDERFLOW";

    case GL_OUT_OF_MEMORY:
      return "GL_OUT_OF_MEMORY";

    case GL_TABLE_TOO_LARGE:
      return "GL_TABLE_TOO_LARGE";

    case GL_INVALID_FRAMEBUFFER_OPERATION:
      return "GL_INVALID_FRAMEBUFFER_OPERATION";

    default:
      return "unknown error";
  }
}

void gl_error_check(std::string context)
{
  unsigned int e = glGetError();

  if (e != GL_NO_ERROR) {
    while (e != GL_NO_ERROR) {
      std::cerr << glstrerror(e) << std::endl;
      e = glGetError();
    }
    throw GLError(Formatter() << "Error(s) found at '" << context << "'");
  }
}
