#include "../../util/exception.hpp"
#include "../../util/debug.hpp"

#include "shader/shader_program.hpp"
#include "buffer_array/buffer_array.hpp"
#include "attrib_array/attrib_array.hpp"
#include "element_array/element_array.hpp"

#include "opengl_renderer.hpp"

void OpenGLRenderer::draw(Scene *scene, const Vec3 &camera_position)
{

    // TODO: this can probably be merged with draw(transform, pos);

    if (scene == nullptr)
        throw UnexpectedNullPointer("Asked to render a scene which was unexpectedly null.");

    // draw the scene
    // TODO any extra drawing required for the scene

    // TODO: z-ordering objects at higher z should be drawn later
    // however I like the tree-structure. To get something to print later, it should be later on in the tree. How do
    // we then make sure something is later in the tree than the player, without it being attached *to* the player?

    // draw its objects
    this->draw((Transform *)scene, camera_position);

}

void OpenGLRenderer::draw(Transform *transform, const Vec3 &camera_position)
{
    if (transform == nullptr)
        return;

    // draw this object
    this->draw(transform->renderable(), camera_position);

    // draw child objects
    for (const auto& child : transform->children()) {
        this->draw(child, camera_position);
    }

    // TODO: recursion detection: maintain a list of objects which have been drawn, keyed to transform address?
}

void OpenGLRenderer::draw(Renderable *renderable, const Vec3 &camera_position) {

    gl_error_check("OpenGLRenderer::draw(Renderable *) -> pre draw");
    if (renderable == nullptr)
        return;

    Vec3 pos = renderable->absolute_position() - camera_position;
    Vec4 colour = renderable->colour();




    auto *renderData = (OpenGLRenderData *)renderable->data();
    if (renderData == nullptr) {
        renderData = new OpenGLRenderData();
        renderable->data( (void *)renderData );

        renderData->shaderProgram = ShaderProgram::from_file(
                "shaders/simple_vert.glsl",
                (renderable->has_texture()?"shaders/textured_frag.glsl":"shaders/block_colour_frag.glsl"));

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

        if (renderable->has_texture()) {
            renderData->texture = Texture::from_file(renderable->texture_path());
        }

    }

    if (renderData->texture) {
        renderable->increment_frame(); // TODO: move to animation loop

        renderData->texture->use();
        Vec4 rect = renderData->texture->get_rect(renderable->current_frame());
        renderData->buffer.set_textured_rect_centred(
                pos*this->scale.promote(1.0f),
                renderable->size()*this->scale,
                colour, rect, renderable->scale());
    }
    else {
        renderData->buffer.set_monochrome_rect_centred(
                pos*this->scale.promote(1.0f),
                renderable->size()*this->scale,
                colour);
    }
    renderData->shaderProgram->use();
    renderData->buffer.use();
    renderData->element.use();

    glDrawElements(GL_TRIANGLES, renderData->element.size(), GL_UNSIGNED_INT, nullptr);
    gl_error_check("OpenGLRenderer::draw(Renderable *) -> post draw");

}