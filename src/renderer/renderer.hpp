#pragma once

#include "../transform/transform.hpp"
#include "../scene/scene.hpp"
#include "../renderable/renderable.hpp"

class Game;
class Renderer {
public:
    Renderer() =default;

    static Renderer *get(Game *game);

    virtual void init() =0;
    virtual void run() =0;
    virtual void clean(Renderable *) =0;

private:
    virtual void draw(Scene *scene) =0;
    virtual void draw(Transform *transform, const Vec3 &camera) =0;
    virtual void draw(Renderable *renderable, const Vec3 &camera) =0;

    Game *game;
    bool fullscreen{
#ifdef DEBUG
        false
#else
        true
#endif
    };

    friend class OpenGLRenderer;
};
