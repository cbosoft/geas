#pragma once

#include "../transform/transform.hpp"

class Scene {
public:
    Scene();
    ~Scene();

    Transform *root;
};