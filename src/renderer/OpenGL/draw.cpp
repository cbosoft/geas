#include "../../util/exception.hpp"
#include "../../util/debug.hpp"

#include "shader/shader_program.hpp"
#include "buffer_array/buffer_array.hpp"
#include "attrib_array/attrib_array.hpp"
#include "element_array/element_array.hpp"

#include "opengl_renderer.hpp"

void OpenGLRenderer::draw(Transform *transform, const Vec3 &camera_position)
{
    if (transform == nullptr)
        return;

    if (!transform->is_enabled())
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

        renderData->texture->use();
        Vec4 rect = renderData->texture->get_rect(renderable->layer(), renderable->current_frame());
        renderData->buffer.set_textured_rect_centred(
                pos*this->scale.promote(1.0f),
                renderable->size()*this->scale*renderable->scale(),
                colour, rect);
    }
    else {
        renderData->buffer.set_monochrome_rect_centred(
                pos*this->scale.promote(1.0f),
                renderable->size()*this->scale*renderable->scale(),
                colour);
    }
    renderData->shaderProgram->use();
    renderData->buffer.use();
    renderData->element.use();

    glDrawElements(GL_TRIANGLES, renderData->element.size(), GL_UNSIGNED_INT, nullptr);
    gl_error_check("OpenGLRenderer::draw(Renderable *) -> post draw");

}