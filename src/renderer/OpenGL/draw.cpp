#include <map>

#include "opengl_renderer.hpp"

void OpenGLRenderer::draw(Scene *scene)
{
    // draw the scene

    // draw its objects
    this->draw(scene->root);
}

void OpenGLRenderer::draw(Transform *transform)
{
    // draw this object
    // TODO

    // draw child objects
    for (const auto& child : transform->children()) {

        this->draw(child);
    }

    // TODO: recursion detection: maintain a list of objects which have been drawn, keyed to transform address?
}