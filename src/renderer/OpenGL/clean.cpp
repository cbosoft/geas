#include "opengl_renderer.hpp"

void OpenGLRenderer::clean(Renderable *renderable)
{
    auto *renderData = (OpenGLRenderData*)renderable->renderer_data;
    delete renderData;
}