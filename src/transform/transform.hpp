#pragma once

#include <list>
#include <mutex>

#include "../vector/vector.hpp"

class Renderable;
class Transform {

  public:
    Transform();
    explicit Transform(Transform *parent);
    virtual ~Transform();

    // Getters
    [[nodiscard]] Vec3 absolute_position() const;
    [[nodiscard]] Vec3 relative_position() const;
    [[nodiscard]] Vec2 scale() const;
    [[nodiscard]] Vec2 local_scale() const;
    [[nodiscard]] Transform *parent() const;
    [[nodiscard]] virtual Renderable *renderable() const;

    // Setters
    void absolute_position(const Vec3& abs);
    virtual void relative_position(const Vec3& rel);
    void scale(const Vec2& scale);
    virtual void local_scale(const Vec2& local_scale);
    void parent(Transform *t);
    void enable();
    void disable();
    bool is_enabled() const;

    Transform &operator +=(const Vec3& other) {
        this->_relative_position += other;
        return *this;
    }

    Transform &operator += (const Vec2& other) {
        this->_relative_position += other.promote(0.0);
        return *this;
    }

    [[nodiscard]] const std::list<Transform*>& children() const;

    void set_static_positioning();
    void set_relative_positioning();
    bool is_static() const;

  private:

    void add_child(Transform *child);

    Vec3 _relative_position;
    Vec2 _local_scale;
    Transform *_parent;
    std::list<Transform *> _children;
    mutable std::mutex _mutex;
    bool _enabled, _static_positioning;
};
