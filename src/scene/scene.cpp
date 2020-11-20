#include "scene.hpp"

Scene::Scene()
    : Transform()
{
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