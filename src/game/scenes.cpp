#include <algorithm>

#include "../util/exception.hpp"
#include "game.hpp"

Scene *Game::active_scene() const
{
    return this->_active_scene;
}

void Game::active_scene(Scene *scene)
{
    if (std::find(this->scenes.begin(), this->scenes.end(), scene) == this->scenes.end()) {
        this->scenes.push_back(scene);
    }
    this->_active_scene = scene;
}

void Game::active_scene(unsigned int i)
{
    if (i < this->scenes.size()) {
        this->_active_scene = this->scenes[i];
    }
    else {
        throw OutOfRange("Scene index is out of range.");
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