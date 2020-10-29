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




    auto it = this->render_info_cache.find(renderable);
    OpenGLRenderData *renderData = nullptr;
    if (it == this->render_info_cache.end()) {
        this->render_info_cache[renderable] = new OpenGLRenderData();

        // renderable not in cache: init new renderdata
        renderData = this->render_info_cache[renderable];
        renderData->shaderProgram = ShaderProgram::from_file("shaders/simple_vert.glsl", "shaders/block_colour_frag.glsl");

        // vertex buffer
        renderData->buffer.add({1.0, 1.0, 0.0, 1.0, 0.0, 1.0, 1.0, 1.0, 1.0});
        renderData->buffer.add({1.0, -1.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0});
        renderData->buffer.add({-1.0, -1.0, 0.0, 1.0, 1.0, 0.0, 1.0, 0.0, 0.0});
        renderData->buffer.add({-1.0, 1.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0});

        // elements
        renderData->element.add(0);
        renderData->element.add(1);
        renderData->element.add(3);
        renderData->element.add(1);
        renderData->element.add(2);
        renderData->element.add(3);

    }
    else {
        // renderable in cache: update with new position/colour?
        renderData = it->second;
    }

    renderData->buffer.set_monochrome_rect_centred(pos, Vec2(0.1f), colour);

    renderData->shaderProgram->use();
    renderData->buffer.use();
    renderData->element.use();

    glDrawElements(GL_TRIANGLES, renderData->element.size(), GL_UNSIGNED_INT, nullptr);
    gl_error_check("OpenGLRenderer::draw(Renderable *) -> post draw");

}