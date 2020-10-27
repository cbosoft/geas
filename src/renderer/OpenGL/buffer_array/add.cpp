#include "buffer_array.hpp"

void BufferArray::add(const GLVertex &vertex)
{
    lock_guard(this->mutex);
    this->_vertices.push_back(vertex);
    this->_invalid = true;
}

void BufferArray::add(const Vec3& position, const Vec4 &colour, const Vec2 &texture)
{
    lock_guard(this->mutex);
    this->_vertices.push_back({
        position.x(), position.y(), position.z(),
        colour.r(), colour.g(), colour.b(), colour.a(),
        texture.x(), texture.y()});
    this->_invalid = true;
}

void BufferArray::add(const Vec3 &position, const Vec2 &texture)
{
    lock_guard(this->mutex);
    this->_vertices.push_back({
        position.x(), position.y(), position.z(),
        1.0f, 1.0f, 1.0f, 1.0f,
        texture.x(), texture.y()});
    this->_invalid = true;
}

void BufferArray::add(const Vec3& position, const Vec4 &colour)
{
    lock_guard(this->mutex);
    this->_vertices.push_back({
        position.x(), position.y(), position.z(),
        colour.r(), colour.g(), colour.b(), colour.a(),
        0.0f, 0.0f});
    this->_invalid = true;
}

void BufferArray::add(const Vec3 &position)
{
    lock_guard(this->mutex);
    this->_vertices.push_back({
        position.x(), position.y(), position.z(),
        1.0f, 1.0f, 1.0f, 1.0f,
        0.0f, 0.0f});
    this->_invalid = true;
}
