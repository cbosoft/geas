#include "../../util/exception.hpp"
#include "../../util/debug.hpp"

#include "shader/shader_program.hpp"
#include "buffer_array/buffer_array.hpp"
#include "attrib_array/attrib_array.hpp"
#include "element_array/element_array.hpp"

#include "opengl_renderer.hpp"

void OpenGLRenderer::draw(Scene *scene)
{

    if (scene == nullptr)
        throw UnexpectedNullPointer("Asked to render a scene which was unexpectedly null.");

    // draw the scene
    // TODO any extra drawing required for the scene

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

void OpenGLRenderer::draw(Renderable *renderable) {

    gl_error_check("OpenGLRenderer::draw(Renderable *) -> pre draw");
    if (renderable == nullptr)
        return;

    Vec3 pos = renderable->absolute_position();
    Vec4 colour = renderable->colour;

    static ShaderProgram *shaderProgram = ShaderProgram::from_file("shaders/simple_vert.glsl", "shaders/block_colour_frag.glsl");
    shaderProgram->use();
    gl_error_check("OpenGLRenderer::draw(Renderable *) -> after shader compile");

    // create vertex buffer
    static BufferArray buff;
    if (buff.size() == 0) {
        buff.add({1.0, 1.0, 0.0, 1.0, 0.0, 1.0, 1.0, 1.0, 1.0});
        buff.add({1.0, -1.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0});
        buff.add({-1.0, -1.0, 0.0, 1.0, 1.0, 0.0, 1.0, 0.0, 0.0});
        buff.add({-1.0, 1.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0});
    }
    buff.use();

    // create vertex attrib array
    static AttribArray attrib;
    attrib.use();

    static ElementArray elements;
    if (elements.size() == 0) {
        elements.add(0);
        elements.add(1);
        elements.add(3);
        elements.add(1);
        elements.add(2);
        elements.add(3);
    }
    elements.use();

    glDrawElements(GL_TRIANGLES, elements.size(), GL_UNSIGNED_INT, 0);
    gl_error_check("OpenGLRenderer::draw(Renderable *) -> post draw");

    debug_msg(Formatter() << "warning: unimplemented function OpenGLRenderer::draw() of renderable at " << pos.to_string());
}