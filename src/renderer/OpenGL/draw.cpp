#include "../../util/exception.hpp"
#include "../../util/debug.hpp"

#include "opengl_renderer.hpp"

void OpenGLRenderer::draw(Scene *scene)
{
    if (scene == nullptr)
        throw UnexpectedNullPointer("Asked to render a scene which was unexpectedly null.");

    // draw the scene

    // draw its objects
    this->draw(scene->root);
}

void OpenGLRenderer::draw(Transform *transform)
{
    if (transform == nullptr)
        return;

    // draw this object
    this->draw(transform->renderable());

    // draw child objects
    for (const auto& child : transform->children()) {

        this->draw(child);
    }

    // TODO: recursion detection: maintain a list of objects which have been drawn, keyed to transform address?
}

void OpenGLRenderer::draw(Renderable *renderable)
{
    if (renderable == nullptr)
        return;

    // TODO: render the renderable
    debug_msg("warning: unimplemented function OpenGLRenderer::draw() called");
}