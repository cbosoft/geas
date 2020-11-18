#pragma once

#include "../transform/transform.hpp"

class Scene : public Transform {
public:
    ~Scene();

    static Scene *from_file(const std::string &path);

private:
    Scene();
};