#pragma once

#include "../transform/transform.hpp"
#include "../geas_object/camera/camera.hpp"


class Scene : public Transform {
public:
    ~Scene();

    static Scene *from_file(const std::string &path);

    Camera *camera();

    virtual bool is_ui() { return false; }

    std::map<std::string, Transform *> layers;
    void set_camera_area(const Vec4 &area);
    void fade_out() const;
    void fade_in() const;

    const std::string &name() const;

    friend class UI;

private:
    explicit Scene(const std::string &name);

    std::string _name;
    Camera *_camera;
};