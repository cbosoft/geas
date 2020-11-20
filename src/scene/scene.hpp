#pragma once

#include "../transform/transform.hpp"
#include "../geas_object/camera/camera.hpp"


// TODO: make scene a derived class of "displayable" which includes UI
class Scene : public Transform {
public:
    ~Scene();

    static Scene *from_file(const std::string &path);

    Camera *camera() const;

private:
    Scene();
    Camera *_camera;
};