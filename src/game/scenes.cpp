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