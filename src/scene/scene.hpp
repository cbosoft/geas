#pragma once

#include "../transform/transform.hpp"
#include "../geas_object/camera/camera.hpp"


// TODO: make scene a derived class of "displayable" which includes UI
class Scene : public Transform {
public:
    ~Scene();

    static Scene *from_file(const std::string &path);

    Camera *camera();

    virtual bool is_ui() { return false; }

    std::map<std::string, Transform *> layers;
    void set_camera_area(const Vec4 &area) const;
    void fade_out() const;
    void fade_in() const;

    friend class UI;

private:
    Scene();
    Camera *_camera;
};