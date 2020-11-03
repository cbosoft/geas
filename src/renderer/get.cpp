#include "renderer.hpp"
#include "OpenGL/opengl_renderer.hpp"

Renderer *Renderer::get(Game *game)
{
    // TODO read settings and return render choice based on that, if I ever move to multiple renderers
    static Renderer *rend = nullptr;

    if (!rend) {
        rend = new OpenGLRenderer();
        rend->game = game;
    }

    return rend;
}