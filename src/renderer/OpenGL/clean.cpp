#include "opengl_renderer.hpp"

void OpenGLRenderer::clean(Renderable *renderable)
{
    auto *renderData = (OpenGLRenderData*)renderable->data();
    delete renderData;
}