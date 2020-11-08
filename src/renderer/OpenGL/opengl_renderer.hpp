#pragma once

#include <list>
#include <map>

#include <GLFW/glfw3.h>

#include "attrib_array/attrib_array.hpp"
#include "buffer_array/buffer_array.hpp"
#include "element_array/element_array.hpp"
#include "shader/shader_program.hpp"
#include "texture/texture.hpp"
#include "../renderer.hpp"

class OpenGLRenderData {
public:
    OpenGLRenderData()
        : shaderProgram(nullptr)
        , texture(nullptr)
    {

    };

    BufferArray buffer;
    ElementArray element;
    ShaderProgram *shaderProgram;
    Texture *texture;
};

class OpenGLRenderer final : public Renderer{
public:
    OpenGLRenderer();
    ~OpenGLRenderer();

    void init() override;
    void run() override;
    void clean(Renderable *renderable) override;

    Vec2 scale{{0.01f, 0.01f}};

private:
    void draw(Scene *scene, const Vec3 &camera) override;
    void draw(Transform *transform, const Vec3 &camera) override;
    void draw(Renderable *renderable, const Vec3 &camera) override;
    bool initialised;

    GLFWwindow *glfw_window;
};