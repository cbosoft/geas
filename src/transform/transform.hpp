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
    void absolute_position(const Vec3& abs);
    virtual void relative_position(const Vec3& rel);
    void scale(const Vec2& scale);
    virtual void local_scale(const Vec2& local_scale);
    void parent(Transform *t);

    Transform &operator +=(const Vec3& other) {
        this->_relative_position += other;
        return *this;
    }

    Transform &operator += (const Vec2& other) {
        this->_relative_position += other.promote(0.0);
        return *this;
    }

  private:
    Vec3 _relative_position;
    Vec2 _local_scale;
    Transform *_parent;
};
