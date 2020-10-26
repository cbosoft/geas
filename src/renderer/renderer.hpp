#pragma once

#include "../transform/transform.hpp"
#include "../scene/scene.hpp"

class Game;
class Renderer {
public:
    Renderer() =default;

    static Renderer *get(Game *game);

    virtual void init() =0;
    virtual void run() =0;

private:
    virtual void draw(Scene *scene) =0;
    virtual void draw(Transform *transform) =0;

    Game *game;

    friend class OpenGLRenderer;
};