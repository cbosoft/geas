#include <algorithm>

#include "../util/exception.hpp"
#include "game.hpp"

Scene *Game::active_scene() const
{
    return this->_active_scene;
}

void Game::active_scene(Scene *scene)
{
    if (this->_active_scene) {
        this->_previous_scene = this->_active_scene;
        this->_previous_scene->disable();
    }

    if (scene) {
        auto it = this->scenes.find(scene->name());
        if (it == this->scenes.end()) {
            this->scenes[scene->name()] = scene;
        } else if (scene != it->second) {
            throw NameConflict(
                    Formatter() << "Scene name conflict found; cannot have two different scenes with the same name (\""
                                << it->first << "\").");
        }
        this->_active_scene = scene;
        this->_active_scene->enable();
    }
    else {
        this->_active_scene = nullptr;
    }
}

void Game::active_scene(const std::string &scene_name)
{
    auto it = this->scenes.find(scene_name);
    if (it != this->scenes.end()) {
        this->_active_scene = this->scenes[scene_name];
        this->_active_scene->activate();
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
    scene->activate();
    c = scene->camera();
    c->fade_in();

    this->set_recently_transitioned();
}

void Game::transition_to(const std::string &scene_name, unsigned int delay_ms)
{
    auto it = this->scenes.find(scene_name);
    if (it == this->scenes.end()) {
        throw OutOfRange(Formatter() << "Could not transition to unknown scene \"" << scene_name << "\". Have you definitely added it?");
    }
    this->transition_to(it->second, delay_ms);
}

void Game::add_scene(Scene *scene)
{
    const std::string &scene_name = scene->name();

    auto it = this->scenes.find(scene_name);
    if (it == this->scenes.end()) {
        this->scenes[scene_name] = scene;
    }
    else {
        throw NameConflict(Formatter() << "tried to add a scene with a name \"" << scene_name << "\"already in use; cannot have two scenes with the same name.");
    }
}

void Game::set_tunnel_tag(const std::string &tag)
{
    this->tunnel_tag = tag;
}

void Game::set_tunnel_tag(const std::string &scene_A, const std::string &scene_B, const std::string &descriptor)
{
    this->set_tunnel_tag(Game::gen_tunnel_tag(scene_A, scene_B, descriptor));
}

std::string Game::get_tunnel_tag()
{
    std::string rv = this->tunnel_tag;
    this->tunnel_tag = "";
    return rv;
}

std::string Game::gen_tunnel_tag(const std::string &scene_A, const std::string &scene_B, const std::string &descriptor)
{
    char Ac = scene_A[0], Bc = scene_B[0];
    const std::string &first = (Ac < Bc ? scene_A : scene_B);
    const std::string &second = (Ac < Bc ? scene_B : scene_A);
    std::string tag = first + "->" + second;
    if (!descriptor.empty()) {
        tag += ":" + descriptor;
    }
    return tag;
}