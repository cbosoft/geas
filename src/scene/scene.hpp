#pragma once

#include "../transform/transform.hpp"
#include "../geas_object/camera/camera.hpp"


class Scene : public Transform {
public:
    explicit Scene(const std::string &name);
    ~Scene();

    Camera *camera() const;
    Transform *hud() const;

    virtual bool is_ui() { return false; }

    std::map<std::string, Transform *> layers;
    void set_camera_area(const Vec4 &area) const;
    void fade_out() const;
    void fade_in() const;

    const std::string &name() const;

    virtual void activate();

private:

    std::string _name;
    Transform *_hud;
    Camera *_camera;
};