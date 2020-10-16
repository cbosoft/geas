#pragma once

#include "../vector/vector.hpp"

class Transform {

  public:
    Transform();
    Transform(Transform *parent);
    ~Transform();

    // Getters
    Vec3 absolute_position() const;
    Vec3 relative_position() const;
    Vec2 scale() const;
    Vec2 local_scale() const;
    Transform *parent() const;

    // Setters
    void absolute_position(Vec3 abs);
    void relative_position(Vec3 rel);
    void scale(Vec2 scale);
    void local_scale(Vec2 local_scale);
    void parent(Transform *t);

  private:
    Vec3 _relative_position;
    Vec2 _local_scale;
    Transform *_parent;
};
