#include <algorithm>

#include "../util/exception.hpp"
#include "game.hpp"

Scene *Game::active_scene() const
{
    if (this->_active_scene == nullptr) {
        // no active scene set currently
        // throw exception
        throw NotFound("Active scene does not exist: set it by index or by ref with Game::active_scene(index_or_ref) after creating it.");
    }

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