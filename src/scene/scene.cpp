#include "scene.hpp"

Scene::Scene()
    : Transform()
{
    // do nothing
    this->_camera = new Camera(this);
}

Scene::~Scene()
{
    // do nothing
}


Camera *Scene::camera() const
{
    return this->_camera;
}


void Scene::set_camera_area(const Vec4 &a) const
{
    this->_camera->area(a);
}