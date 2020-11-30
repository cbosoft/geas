#include <algorithm>

#include "../util/exception.hpp"
#include "game.hpp"

Scene *Game::active_scene() const
{
    return this->_active_scene;
}

void Game::active_scene(Scene *scene)
{
    this->_active_scene = scene;
}

void Game::active_scene(const std::string &scene_name)
{
    auto it = this->scenes.find(scene_name);
    if (it != this->scenes.end()) {
        this->_active_scene = this->scenes[scene_name];
    }
    else {
        throw OutOfRange(Formatter() << "Scene \"" << scene_name << "\" is unknown to game; have you added it?");
    }
}

void Game::transition_to(Scene *scene, unsigned int delay_ms)
{
    Camera *c = nullptr;
    if (this->active_scene()) {
        c = this->active_scene()->camera();
        c->fade_out();
        std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
        this->active_scene()->disable();
        this->active_scene(nullptr);
        c = nullptr;
    }
    else {
        std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
    }
    this->active_scene(scene);
    scene->enable();
    c = scene->camera();
    c->fade_in();
}