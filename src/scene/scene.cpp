#include "scene.hpp"

Scene::Scene()
    : Transform()
    , _camera(nullptr)
{
    // do nothing
}

Scene::~Scene()
{
    // do nothing
}


Camera *Scene::camera()
{
    if (!this->_camera) {
        this->_camera = new Camera(this);
        this->_camera->enable();
    }
    return this->_camera;
}


void Scene::set_camera_area(const Vec4 &a) const
{
    this->_camera->area(a);
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