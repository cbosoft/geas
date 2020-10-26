#pragma once

#include <GLFW/glfw3.h>

#include "../renderer.hpp"

class OpenGLRenderer final : public Renderer{
public:
    OpenGLRenderer();
    ~OpenGLRenderer();

    void init() override;
    void run() override;


private:
    void draw(Scene *scene) override;
    void draw(Transform *transform) override;
    bool initialised;

    GLFWwindow *glfw_window;
};