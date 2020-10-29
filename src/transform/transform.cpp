#include "transform.hpp"

Transform::Transform()
    : _relative_position(Vec3(0.0))
    , _local_scale(Vec2(1.0))
    , _parent(nullptr)
{
  // do nothing
}

Transform::Transform(Transform *parent)
  :
    _relative_position(Vec3(0.0))
    , _local_scale(Vec2(1.0))
    , _parent(parent)
{
    parent->add_child(this);
}

Transform::~Transform()
{
    // do nothing
}


// Getters
Vec3 Transform::absolute_position() const
{
    Vec3 abs_pos = this->relative_position();
    if (this->_parent) {
        abs_pos += this->_parent->absolute_position();
    }
    return abs_pos;
}

Vec3 Transform::relative_position() const
{
    std::scoped_lock _sl(this->_mutex);
    return this->_relative_position;
}

Vec2 Transform::scale() const
{
    Vec2 scale = this->local_scale();
    if (this->_parent) {
        scale *= this->_parent->scale();
    }
    return scale;
}

Vec2 Transform::local_scale() const
{
    std::scoped_lock _sl(this->_mutex);
    return this->_local_scale;
}

Transform *Transform::parent() const
{
    std::scoped_lock _sl(this->_mutex);
    return this->_parent;
}

// Setters
void Transform::absolute_position(const Vec3& abs)
{
    if (this->_parent) {
        this->relative_position(abs - this->_parent->absolute_position());
    }
    else {
        this->relative_position(abs);
    }
}

void Transform::relative_position(const Vec3& rel)
{
    std::scoped_lock _sl(this->_mutex);
    this->_relative_position = rel;
}

void Transform::scale(const Vec2& scale)
{
    if (this->_parent) {
        this->local_scale(scale / this->_parent->scale());
    }
    else {
        this->local_scale(scale);
    }
}

void Transform::local_scale(const Vec2& local_scale)
{
    std::scoped_lock _sl(this->_mutex);
    this->_local_scale = local_scale;
}

void Transform::parent(Transform *parent)
{
    std::scoped_lock _sl(this->_mutex);
    this->_parent = parent;
}

const std::list<Transform *>& Transform::children() const
{
    std::scoped_lock _sl(this->_mutex);
    return this->_children;
}

Renderable *Transform::renderable() const
{
    return nullptr;
}

void Transform::add_child(Transform *child)
{
    std::scoped_lock _sl(this->_mutex);
    this->_children.push_back(child);
}