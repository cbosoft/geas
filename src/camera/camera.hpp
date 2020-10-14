#pragma once

#include <string>

#include "../vector/vector.hpp"

class Camera {

  public:

    static Camera *create(std::string name="");
    static Camera *create(float x, float y, float w, float h, std::string name="");

    static Camera *main();
    static Camera *by_name(std::string name);
    static Camera *by_index(int index);

    void set_position(Vec2 position);
    void set_size(Vec2 size);
    const Vec2& get_position() const;
    const Vec2& get_size() const;

    Vec2 world_to_window(Vec2 world);
    Vec2 window_to_world(Vec2 window);
    Vec3 world_to_window(Vec3 world);
    Vec3 window_to_world(Vec3 window);

  private:
    Camera(float x, float y, float w, float h);

    Vec2 position, size, _inv_size;
    Vec3 _position3d, _size3d, _inv_size3d;

};
