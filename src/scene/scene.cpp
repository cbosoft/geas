#include <iostream>
#include "scene.hpp"

Scene::Scene(const std::string &name)
    : Transform()
    , _name(name)
    , _hud(new Transform(this))
    , _camera(new Camera(this))
{
    // do nothing
}

Scene::~Scene()
{
    // do nothing
}


Camera *Scene::camera() const
{
    return this->_camera;
}

Transform *Scene::hud() const
{
    return this->_hud;
}


void Scene::set_camera_area(const Vec4 &a) const
{
    this->camera()->area(a);
}

void Scene::fade_out() const
{
    if (this->_camera) {
        this->_camera->fade_out();
    }
}

void Scene::fade_in() const
{
    if (this->_camera)
        this->_camera->fade_in();
}

const std::string &Scene::name() const
{
    return this->_name;
}

void Scene::activate()
{
    this->enable();
}