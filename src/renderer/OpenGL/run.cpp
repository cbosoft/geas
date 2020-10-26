#include "../../game/game.hpp"

#include "opengl_renderer.hpp"

void OpenGLRenderer::run()
{

    if (!this->initialised)
        this->init();

    while (!glfwWindowShouldClose(this->glfw_window)) {

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(glfw_window);

        /* Poll for and process events */
        glfwPollEvents();
        Scene *scene = this->game->active_scene();

        this->draw(scene);



        if (!this->game->is_alive()) {
            glfwSetWindowShouldClose(this->glfw_window, true);
        }
    }
}