#pragma once

#include <list>
#include <map>

#include <GLFW/glfw3.h>

#include "attrib_array/attrib_array.hpp"
#include "buffer_array/buffer_array.hpp"
#include "element_array/element_array.hpp"
#include "shader/shader_program.hpp"
#include "../renderer.hpp"

class OpenGLRenderData {
public:
    OpenGLRenderData() =default;

    BufferArray buffer;
    ElementArray element;
    ShaderProgram *shaderProgram;
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
    void draw(Scene *scene) override;
    void draw(Transform *transform) override;
    void draw(Renderable *renderable) override;
    bool initialised;

    GLFWwindow *glfw_window;
};