#include "opengl_renderer.hpp"

OpenGLRenderer::OpenGLRenderer()
    : initialised(false)
{
    // do nothing
}

OpenGLRenderer::~OpenGLRenderer()
{
    if (this->initialised) {
        glfwTerminate();
    }
}