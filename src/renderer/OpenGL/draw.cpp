#include "../../util/exception.hpp"
#include "../../util/debug.hpp"

#include "shader/shader.hpp"

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

    Vec3 pos = renderable->absolute_position();
    Vec4 colour = renderable->colour;

    ShaderProgram *shaderProgram = ShaderProgram::from_file("shaders/simple_vert.glsl", "shaders/block_colour_frag.glsl");
    shaderProgram->use();

    // create vertex buffer
    // create vertex attrib array

    debug_msg(Formatter() << "warning: unimplemented function OpenGLRenderer::draw() of renderable at " << pos.to_string());
}