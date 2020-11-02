#include <chrono>
#include <iostream>

#include "../../game/game.hpp"

#include "opengl_renderer.hpp"

void OpenGLRenderer::run()
{

    if (!this->initialised)
        this->init();

    // std::chrono::time_point<std::chrono::system_clock> t0 = std::chrono::system_clock::now();

    while (!glfwWindowShouldClose(this->glfw_window)) {

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        Scene *scene = this->game->active_scene();
        this->draw(scene);

        /* Swap front and back buffers */
        glfwSwapBuffers(glfw_window);

        /* Poll for and process events */
        glfwPollEvents();

        if (!this->game->is_alive()) {
            glfwSetWindowShouldClose(this->glfw_window, true);
        }

        // std::chrono::time_point<std::chrono::system_clock> t1 = std::chrono::system_clock::now();
        // int dt_us = std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0).count();
        // std::cerr << "fps = " << 1.0/(1e-6*static_cast<float> (dt_us)) << std::endl;
        // t0 = t1;
    }
}