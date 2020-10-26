#include "scene.hpp"

Scene::Scene()
    : root(new Transform())
{
    // do nothing
}

Scene::~Scene()
{
    delete this->root;
}